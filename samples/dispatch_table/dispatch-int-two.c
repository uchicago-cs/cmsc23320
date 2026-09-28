#include <stdlib.h>
#include <stdio.h>
#include "handlers.h"

typedef int (*handler_function)(int, int, int*);

static const handler_function handlers[] = { 
                                 handle_ADD, 
                                 handle_SUB, 
                                 handle_MLT,
                                 handle_DIV 
                              };

static const int num_handlers = sizeof(handlers) / sizeof(handlers[0]);

int main(int argc, char **argv)
{
    int code, a, b, x, rc;

    if(argc!=4)
    {
        fprintf(stderr, "Usage: %s intcode a b\n", argv[0]);
        return 1;
    }

    code = atoi(argv[1]);   
    a = atoi(argv[2]);   
    b = atoi(argv[3]);   

    if (code < 0 || code >= num_handlers)
    {
        fprintf(stderr, "Unknown handler code %i\n", code);
        return 2;
    }

    rc = handlers[code](a, b, &x);

    /* x is only set if the handler succeeded, so we must check rc before using it */
    if (rc == 0)
        printf("Result: %i\n", x);
    else
        fprintf(stderr, "Handler returned error code %i\n", rc);

    return 0;
}
