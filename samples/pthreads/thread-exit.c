/* 
 *
 *  CMSC 23320 - Foundations of Computer Networks
 * 
 *  Simple example of how to make a thread exit gracefully.
 * 
 *  This program creates a thread (the "hello thread") that
 *  will print a message every five seconds until it exits.
 *  The program's main thread will wait for the user to press
 *  a key and, when they do, will signal the "hello thread"
 *  to exit.   
 *    
 *  Written by: Borja Sotomayor
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <pthread.h>

/* Context object to share information
 * between the two threads */
typedef struct ctx
{
    /* If true, the "hello thread" must continue to 
     * print out a message. If false, the thread must exit */
    bool active;

    /* Mutex and condition variable that will allow the
     * main thread to signal the "hello thread" */
    pthread_mutex_t lock;
    pthread_cond_t cv;
} ctx_t;


/* Function that will be run by the "hello thread" */
void *hello_thread_func(void *args)
{
    /* Get the context object from the args */
    ctx_t *ctx = (ctx_t *) args;
    int rc;
    struct timespec ts;

    /* Thread loop. We keep looking until ctx->active is false */
    pthread_mutex_lock(&ctx->lock);
    while (ctx->active)
    {
        /* Get current time */
        clock_gettime(CLOCK_REALTIME, &ts);

        /* Wait on the condition variable, with a 5 second timeout */
        ts.tv_sec += 5;
        rc = pthread_cond_timedwait(&ctx->cv, &ctx->lock, &ts);
        if (rc == ETIMEDOUT)
        {
            printf("[HELLO THREAD] Hello!\n");
        }
        else
        {
            printf("[HELLO THREAD] I woke up and it wasn't because of a timeout.\n");
        }
    }

    printf("[HELLO THREAD] I'm done!\n");

    /* Strictly speaking, this is not necessary because we could also just
     * allow the function to return. */
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    pthread_t hello_thread;
    ctx_t *ctx;

    /* Allocate an initialize the context object */
    ctx = calloc(1, sizeof(ctx_t));
    ctx->active = true;
    pthread_mutex_init(&ctx->lock, NULL);
    pthread_cond_init(&ctx->cv, NULL);

    /* Create the "hello thread" */
    if (pthread_create(&hello_thread, NULL, hello_thread_func, ctx) != 0)
    {
        perror("Could not create thread");
        free(ctx);
        return EXIT_FAILURE;
    }

    /* Wait for user to press a key */
    printf("[MAIN  THREAD] Press any key to tell the hello thread to exit.\n");
    getchar();

    /* Switch ctx->active to false, and signal "hello thread"
    pthread_mutex_lock(&ctx->lock);
    ctx->active = false;
    pthread_cond_signal(&ctx->cv);
    pthread_mutex_unlock(&ctx->lock);

    /* Join the "hello thread" */
    pthread_join(hello_thread, NULL);

    /* Free resources */
    pthread_mutex_destroy(&ctx->lock);
    pthread_cond_destroy(&ctx->cv);
    free(ctx);

    printf("[MAIN  THREAD] I'm done!\n");

    return EXIT_SUCCESS;
}