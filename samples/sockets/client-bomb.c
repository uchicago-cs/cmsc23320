/* 
 *
 *  CMSC 23320 - Foundations of Computer Networks
 *  
 *  A client that bombs a server with N connections
 *
 *  Usage:
 *
 *      ./client-bomb -h <host> -p <port> -n <number of connections>
 *  
 *  Written by: Borja Sotomayor
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* Prints a usage message to stderr and exits */
static void usage(const char *prog)
{
    fprintf(stderr, "USAGE: %s -h HOST -p PORT -n NUM_CONNECTIONS\n", prog);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int *sockets, nsockets = -1;
    struct addrinfo hints, *res, *p;
    char *host = NULL, *port = NULL;
    int opt, i, rc;

    while ((opt = getopt(argc, argv, "h:p:n:")) != -1)
        switch (opt)
        {
            case 'h':
                host = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            case 'n':
                nsockets = atoi(optarg);
                break;
            default:
                /* getopt() has already printed an error message */
                usage(argv[0]);
        }

    if(host == NULL || port == NULL || nsockets < 1)
        usage(argv[0]);

    sockets = calloc(nsockets, sizeof(int));
    if (sockets == NULL)
    {
        perror("Could not allocate memory for sockets");
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rc = getaddrinfo(host, port, &hints, &res)) != 0)
    {
        fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(rc));
        exit(EXIT_FAILURE);
    }

    for(p = res;p != NULL; p = p->ai_next) 
    {
        if ((sockets[0] = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
            perror("Could not open socket");
            continue;
        }

        if (connect(sockets[0], p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockets[0]);
            perror("Could not connect to socket");
            continue;
        }

        break;
    }
    
    if (p == NULL)
    {
        fprintf(stderr, "Could not find a socket to connect to.\n");
        exit(EXIT_FAILURE);
    }

    /* Bomb! */
    printf("Bombing with %d\n", nsockets);
    for(i=1; i<nsockets; i++)
    {
        if ((sockets[i] = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("Could not open socket");
            continue;
        }

        if (connect(sockets[i], p->ai_addr, p->ai_addrlen) == -1)
        {
            perror("Could not connect to socket");
            close(sockets[i]);
            sockets[i] = -1;
        }
    }
    sleep(2);

    for(i=0; i<nsockets; i++)
    {
        if (sockets[i] != -1)
            close(sockets[i]);
    }
    printf("Done\n");

    freeaddrinfo(res);
    return EXIT_SUCCESS;
}
