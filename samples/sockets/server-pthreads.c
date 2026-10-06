/* 
 *
 *  CMSC 23320 - Foundations of Computer Networks
 *  
 *  A simple multi-threaded server
 *  
 *  Written by: Borja Sotomayor
 *
 *  To compile:
 *
 *      gcc server-pthreads.c -o server-pthreads -pthread
 *
 *  To run:
 *
 *      ./server-pthreads
 *
 *  The server will listen on port 23320. You can connect to
 *  it from a telnet session like this:
 *
 *      telnet localhost 23320
 *
 *  Do this multiple time to observe how the server can support
 *  multiple connections at the same time.
 *
 */
#include <stdio.h>
#include <stdlib.h>
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

/* We will use this struct to pass parameters to one of the threads */
struct worker_args
{
    int socket;
};

/* Forward declaration. See below for details. */
void *service_single_client(void *args);

int main(void)
{
    /* If a client closes a connection, this will generally produce a SIGPIPE
       signal that will kill the process. We want to ignore this signal, so
       send() just returns -1 when this happens. */
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        perror("Unable to ignore SIGPIPE");
        exit(-1);
    }


    /* The following code sets up the server socket to accept connections.
       The socket code is similar to oneshot-single.c, except that we will
       use getaddrinfo() to get the sockaddr (instead of creating it manually)
       and we will use sockaddr_storage when accepting a client connection
       (instead of using sockaddr_in). sockaddr_storage is large enough to hold
       any type of address, so this is good practice even though this server
       only accepts IPv4 connections.

       Additionally, this function will spawn a new thread for each new client
       connection.

       See oneshot-single.c and client.c for more documentation on how the socket
       code works.
     */
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
    hints.ai_flags = AI_PASSIVE; // Return my address, so I can bind() to it

    /* Note how we call getaddrinfo with the host parameter set to NULL */
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

        if (listen(server_socket, SOMAXCONN) == -1)
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

    /* Loop and wait for connections */
    while (1)
    {
        /* Call accept(). At this point, we will block until a client establishes a connection.
           Note that accept() uses sin_size both as an input (the size of client_addr) and as
           an output (the size of the address it actually stored), so we need to reset it
           before every call to accept() */
        sin_size = sizeof(client_addr);
        if ((client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &sin_size)) == -1)
        {
            /* If this particular connection fails, no need to kill the entire thread. */
            perror("Could not accept() connection");
            continue;
        }

        /* We're now connected to a client. We're going to spawn a "worker thread" to handle
           that connection. That way, the server thread can continue running, accept more connections,
           and spawn more threads to handle them.

           New threads are created using the pthread_create function.
           - The first parameter is a pointer to a pthread_t variable, which we can use
             in the remainder of the program to manage this thread.
           - The second parameter is used to specify the attributes of this new thread
             (e.g., its stack size). We can leave it NULL here.
           - The third parameter is the function this thread will run. This function *must*
             have the following prototype:

               void *f(void *args);

             Note how the function expects a single parameter of type void*. In this case,
             the thread function will be service_single_client.
           - The fourth parameter to pthread_create is used to specify the parameter
             to the thread function. In this case, the worker thread needs to know what socket
             it must use to communicate with the client, so we'll pass the client_socket as a
             parameter to the thread. Although we could arguably just pass a pointer to client_socket,
             it is good practice to use a struct that encapsulates the parameters to the thread
             (even if there is only one parameter). In this case, this is done with the worker_args struct.
        */
        wa = calloc(1, sizeof(struct worker_args));
        if (wa == NULL)
        {
            perror("Could not allocate memory for worker thread");
            close(client_socket);
            continue;
        }
        wa->socket = client_socket;

        if (pthread_create(&worker_thread, NULL, service_single_client, wa) != 0)
        {
            perror("Could not create a worker thread");
            free(wa);
            close(client_socket);
            close(server_socket);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}



/* This is the function that is run by the "worker thread".
   It is in charge of "handling" an individual connection and, in this case
   all it will do is send a message every five seconds until the connection
   is closed.

   See oneshot-single.c and client.c for more documentation on how the socket
   code works.
 */
void *service_single_client(void *args) {
    struct worker_args *wa;
    int socket, nbytes;
    char tosend[100];

    /* Unpack the arguments */
    wa = (struct worker_args*) args;
    socket = wa->socket;

    /* This tells the pthreads library that no other thread is going to
       join() this thread. This means that, once this thread terminates,
       its resources can be safely freed (instead of keeping them around
       so they can be collected by another thread join()-ing this thread) */
    pthread_detach(pthread_self());

    fprintf(stderr, "Socket %d connected\n", socket);

    while(1)
    {
        snprintf(tosend, sizeof(tosend), "%d -- Hello, socket!\n", (int) time(NULL));

        nbytes = send(socket, tosend, strlen(tosend), 0);

        if (nbytes == -1 && (errno == ECONNRESET || errno == EPIPE))
        {
            fprintf(stderr, "Socket %d disconnected\n", socket);
            close(socket);
            free(wa);
            pthread_exit(NULL);
        }
        else if (nbytes == -1)
        {
            perror("Unexpected error in send()");
            close(socket);
            free(wa);
            pthread_exit(NULL);
        }
        sleep(5);
    }

    pthread_exit(NULL);
}

