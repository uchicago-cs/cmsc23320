/* 
 *
 *  CMSC 23320 - Foundations of Computer Networks
 *  
 *  A simple multi-threaded server that uses a condition variable to signal an event from one thread to another.
 *  More specifically, when the server accepts a connection, it will create a thread, but will not accept any
 *  more connections until a "HELLO" command is received through the connection that was just accepted. So,
 *  the worker thread needs to signal when this happens. Optionally, we can specify a timeout for waiting
 *  for the connection to receive a HELLO command.
 *
 *  The code is very similar to server-pthreads-mutex.c. Look for comments with the text
 *  "ADDED" to see what has been changed exactly.
 *  
 *  Written by: Borja Sotomayor
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

/* ADDED: Each worker thread now has a state (stored in its worker_args struct)
 * that indicates whether it has received a HELLO command. The server context
 * contains a condition variable (and corresponding mutex) that the worker
 * threads use to signal the main thread when their state changes.
 */

enum worker_thread_state
{
    STARTING,    /* The thread is starting */
    HELLO_RCVD,  /* The thread has received a HELLO command */
    ERROR        /* An error has occurred when starting the thread */
};

struct server_ctx
{
    pthread_mutex_t lock;
    pthread_cond_t cv_hello_rcvd;
};

/* ADDED: The worker_args struct is now accessed by both the main thread and the
 * worker thread (protected by ctx->lock). Since the main thread may stop waiting
 * on the worker thread (if a timeout is used), we can't free this struct as soon
 * as the main thread is done with it: the worker thread may still need it.
 * So, we keep track of whether the main thread is still waiting on the worker
 * thread, and whichever thread is the last one to use the struct frees it.
 */
struct worker_args
{
    int socket;
    struct server_ctx *ctx;
    enum worker_thread_state state;  /* State of this worker thread */
    bool main_waiting;               /* Is the main thread still waiting on this worker thread? */
};

void *service_single_client(void *args);

int main(int argc, char *argv[])
{
    /* ADDED: If there is a command-line parameter, we interpret it as a timeout
     * in seconds to use when waiting for a thread to complete its startup */
    long int timeout = 0;
    if(argc == 2)
    {
        timeout = strtol(argv[1], NULL, 10);
        if (timeout < 0)
            timeout = 0;
    }

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        perror("Unable to ignore SIGPIPE");
        exit(-1);
    }

    /* ADDED: Initializing a condition variable and its lock */
    struct server_ctx *ctx = calloc(1, sizeof(struct server_ctx));
    if (ctx == NULL)
    {
        perror("Could not allocate server context");
        return EXIT_FAILURE;
    }
    pthread_mutex_init(&ctx->lock, NULL);
    pthread_cond_init(&ctx->cv_hello_rcvd, NULL);

    int server_socket;
    int client_socket;
    pthread_t worker_thread;
    struct addrinfo hints, *res, *p;
    struct sockaddr_storage client_addr;
    socklen_t sin_size;
    struct worker_args *wa;
    int yes = 1;
    int rc;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rc = getaddrinfo(NULL, "23320", &hints, &res)) != 0)
    {
        fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(rc));
        return EXIT_FAILURE;
    }

    for(p = res;p != NULL; p = p->ai_next)
    {
        if ((server_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("Could not open socket");
            continue;
        }

        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("Socket setsockopt() failed");
            close(server_socket);
            continue;
        }

        if (bind(server_socket, p->ai_addr, p->ai_addrlen) == -1)
        {
            perror("Socket bind() failed");
            close(server_socket);
            continue;
        }

        if (listen(server_socket, 5) == -1)
        {
            perror("Socket listen() failed");
            close(server_socket);
            continue;
        }

        break;
    }

    freeaddrinfo(res);

    if (p == NULL)
    {
        fprintf(stderr, "Could not find a socket to bind to.\n");
        return EXIT_FAILURE;
    }

    while (1)
    {
        sin_size = sizeof(client_addr);
        if ((client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &sin_size)) == -1)
        {
            perror("Could not accept() connection");
            continue;
        }

        wa = calloc(1, sizeof(struct worker_args));
        if (wa == NULL)
        {
            perror("Could not allocate memory for worker thread");
            close(client_socket);
            continue;
        }
        wa->socket = client_socket;
        wa->ctx = ctx;
        wa->state = STARTING;
        wa->main_waiting = true;

        pthread_mutex_lock(&ctx->lock);
        if (pthread_create(&worker_thread, NULL, service_single_client, wa) != 0)
        {
            perror("Could not create a worker thread");
            free(wa);
            close(client_socket);
            close(server_socket);
            return EXIT_FAILURE;
        }

        /* ADDED: If a timeout was specified, we compute the deadline (pthread_cond_timedwait
         * expects an absolute time, not a duration) *before* we start waiting. If we computed
         * it inside the loop, every spurious wakeup would restart the timeout from scratch. */
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += timeout;

        /* ADDED: we use the condition variable to wait until wa->state is not starting */
        printf("main(): Waiting for thread to finish starting %d.\n", client_socket);
        while(wa->state == STARTING)
        {
            if(timeout == 0)
            {
                /* If not timeout is specified, we use pthread_cond_wait */
                pthread_cond_wait(&ctx->cv_hello_rcvd, &ctx->lock);
            }
            else
            {
                /* If a timeout was specified, we use pthread_cond_timedwait */
                rc = pthread_cond_timedwait(&ctx->cv_hello_rcvd, &ctx->lock, &ts);
                if (rc == ETIMEDOUT)
                {
                    printf("main(): Thread for socket %d timed out.\n", client_socket);
                    break;
                }
            }
        }

        if(wa->state == HELLO_RCVD)
        {
            printf("main(): Thread for socket %d reports receiving HELLO.\n", client_socket);
        }
        else if(wa->state == ERROR)
        {
            printf("main(): Thread for socket %d did not start up correctly.\n", client_socket);
        }

        /* ADDED: The main thread is done with wa. If the worker thread has already
         * reported its state, it is done with wa too, so we free it. Otherwise (because
         * we timed out), the worker thread will free it when it reports its state. */
        wa->main_waiting = false;
        if(wa->state != STARTING)
            free(wa);
        pthread_mutex_unlock(&ctx->lock);
    }

    /* ADDED: Destroying a condition variable and its lock */
    pthread_mutex_destroy(&ctx->lock);
    pthread_cond_destroy(&ctx->cv_hello_rcvd);
    free(ctx);

    return EXIT_SUCCESS;
}


void *service_single_client(void *args)
{
    struct worker_args *wa;
    struct server_ctx *ctx;
    int socket, nbytes;
    char *msg;
    char buffer[100];
    bool error = false;
    bool wrong_cmd = true;

    wa = (struct worker_args*) args;
    socket = wa->socket;
    ctx = wa->ctx;

    printf("(%d) service_single_client(): Waiting for HELLO.\n", socket);

    pthread_detach(pthread_self());

    /* ADDED: The rest of the function is different from the mutex example.
     *
     * Note: this code also provides an example of an acceptable way of using goto statements
     *       (see https://uchicago-cs.github.io/student-resource-guide/style-guide/c.html#goto-statements)
     */

    /* We send a message to the client. */
    msg = "HELLO?\r\n";
    if(send(socket, msg, strlen(msg), 0) <= 0)
    {
        perror("Socket send() failed");
        error = true;
        goto out;
    }

    /* Client needs to send back a HELLO */
    nbytes = recv(socket, buffer, sizeof(buffer), 0);
    if (nbytes <= 0)
    {
        if (nbytes == 0)
        {
            printf("(%d) service_single_client(): Disconnected.\n", socket);
        } else if (nbytes < 0)
        {
            perror("Socket recv() failed");
        }

        error = true;
        goto out;
    }
    else if (nbytes >= 5)
    {
        msg = "HELLO";
        if (strncmp(msg, buffer, strlen(msg)) == 0)
            wrong_cmd = false;
    }

    /* We send back a message */
    if (wrong_cmd)
    {
        msg = "ACCESS DENIED!\r\n";
    }
    else
    {
        msg = "ACCESS GRANTED\r\n";
    }

    if (send(socket, msg, strlen(msg), 0) <= 0)
    {
        perror("Socket send() failed");
        error = true;
        goto out;
    }

out:
    /* Change the value of wa->state and signal the condition variable */
    pthread_mutex_lock(&ctx->lock);
    if (error)
    {
        printf("(%d) service_single_client(): Socket error.\n", socket);
        wa->state = ERROR;
    }
    else if (wrong_cmd)
    {
        printf("(%d) service_single_client(): Wrong command received.\n", socket);
        wa->state = ERROR;
    }
    else
    {
        printf("(%d) service_single_client(): HELLO received.\n", socket);
        wa->state = HELLO_RCVD;
    }

    if (wa->main_waiting)
    {
        /* The main thread will free wa once it wakes up, so we must not
         * access wa after we release the lock */
        pthread_cond_signal(&ctx->cv_hello_rcvd);
    }
    else
    {
        /* The main thread timed out waiting for this thread, and has moved
         * on to other connections. Nobody is waiting for our signal, and we are
         * the last thread using wa, so we free it. */
        free(wa);
    }
    pthread_mutex_unlock(&ctx->lock);

    /* If there was an error or we received the wrong command, we close the connection
     * and exit the thread */
    if(error || wrong_cmd)
    {
        close(socket);
        pthread_exit(NULL);
    }

    /* At this point, we just keep the connection open until
     * the client disconnects (we ignore anything that is
     * received */
    while(1)
    {
        nbytes = recv(socket, buffer, sizeof(buffer), 0);
        if (nbytes == 0)
            break;
        else if (nbytes == -1)
        {

            close(socket);
            pthread_exit(NULL);
        }
    }

    printf("(%d) service_single_client(): Disconnected.\n", socket);
    close(socket);
    pthread_exit(NULL);
}

