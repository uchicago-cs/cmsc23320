/* 
 *
 *  CMSC 23320 - Foundations of Computer Networks
 *  
 *  A very simple socket client. Reads at most 100 bytes from a socket and quits.
 *  
 *  Written by: Borja Sotomayor
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

int main(int argc, char *argv[])
{
    /* A socket is just a file descriptor, i.e., an int */
    int active_socket;

    /* The addrinfo struct is used both as a parameter to getaddrinfo (to provide "hints" on
       what type of address we're using), and as a way to return the addresses associated
       to a given hostname and service. For example, "www.google.com" (with service "http")
       might resolve to multiple IP addresses, and one port (80). So, addrinfo is
       actually a linked list:

           struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               size_t           ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
           };

       Note how it contains information used in other socket functions (family, socket type, etc.)
       and the sockaddr for the address.

       We need to declare three addrinfo's: */
    struct addrinfo hints, // Used to provide hints to getaddrinfo()
                    *res,  // Used to return the list of addrinfo's
                    *p;    // Used to iterate over this list


    /* Host and port */
    char *host = NULL, *port = NULL;

    /* Buffer to receive bytes from the socket */
    char buffer[100 + 1]; // +1 for '\0'

    /* Number of bytes received */
    int nbytes;

    /* Used by getopt */
    int opt;

    /* Return value of getaddrinfo() */
    int rc;

    /* Use getopt to fetch the host and port */
    while ((opt = getopt(argc, argv, "h:p:")) != -1)
        switch (opt)
        {
            case 'h':
                host = optarg;
                break;
            case 'p':
                port = optarg;
                break;
            default:
                printf("Unknown option\n"); exit(1);
        }

    if(host == NULL || port == NULL)
    {
        printf("USAGE: client -h HOST -p PORT\n");
        exit(1);
    }

    /* We start by creating the "hints" addrinfo that is used to aid
       getaddrinfo in returning addresses that we'll actually be able
       to use */

    /* We want to leave all unused fields of hints to zero*/
    memset(&hints, 0, sizeof(hints));

    /* We leave the family unspecified. Based on the hostname (or IP address), 
       getaddrinfo should be able to determine what family we want to use.
       However, we can set this to AF_INET or AF_INET6 to force a specific version */
    hints.ai_family = AF_UNSPEC;

    /* We want a reliable, full-duplex socket */
    hints.ai_socktype = SOCK_STREAM;

    /* Call getaddrinfo with the host and port specified in the command line */
    if ((rc = getaddrinfo(host, port, &hints, &res)) != 0)
    {
        /* getaddrinfo() doesn't set errno, so we can't use perror().
           Instead, it returns an error code that we can convert to
           a string with gai_strerror() */
        fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(rc));
        exit(-1);
    }

    /* Iterate through the list */
    for(p = res;p != NULL; p = p->ai_next) 
    {
        /* The list could potentially include multiple entries (e.g., if a
           hostname resolves to multiple IP addresses). Here we just pick
           the first address we can connect to, although we could do
           additional filtering (e.g., we may prefer IPv6 addresses to IPv4
           addresses */

        /* Try to open a socket */
        if ((active_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("Could not open socket");
            continue;
        }

        /* Try to connect.
           Note: Like many other socket functions, this function expects a sockaddr and
                 its length, both of which are conveniently provided in addrinfo */
        if (connect(active_socket, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(active_socket);
            perror("Could not connect to socket");
            continue;
        }

        /* If we make it this far, we've connected succesfully. Don't check any more entries */
        break;
    }
    
    /* We don't need the linked list anymore. Free it. */
    freeaddrinfo(res);

    /* If we reached the end of the list, we couldn't connect to any of the addresses */
    if (p == NULL)
    {
        fprintf(stderr, "Could not connect to %s:%s\n", host, port);
        exit(-1);
    }

    /* Read from the socket */
    nbytes = recv(active_socket, buffer, sizeof(buffer) - 1, 0);
    if (nbytes == 0)
    {
        fprintf(stderr, "Server closed the connection\n");
        close(active_socket);
        exit(-1);
    }
    else if (nbytes == -1)
    {
        perror("Socket recv() failed");
        close(active_socket);
        exit(-1);
    }
    else
    {
        /* The message doesn't have a '\0' at the end. Add one so we
           can print it */
        buffer[nbytes] = '\0';
        printf("Received this message:\n<<%s>>\n", buffer);
    }

    /* Note: The above assumes that the message will arrive in a single packet, which
       may not always be the case. */

    close(active_socket);

    return 0;
}
