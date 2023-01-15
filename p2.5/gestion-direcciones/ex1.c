#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USAGE "Usage: %s host\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error_gai(code_error) \
          do { fprintf(stderr, "Error in getaddrinfo(): %s\n", gai_strerror(code_error)); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints, *res; //for getaddrinfo()
    char host[200]; //for getnameinfo()
    int e; //error code

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    if((e = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) handle_error_gai(e);
     

    for(struct addrinfo *rp = res; rp != NULL; rp = rp->ai_next){
        getnameinfo(rp->ai_addr, rp->ai_addrlen, host, 200, NULL, 0, NI_NUMERICHOST);
        printf("%s\t%d\t%d\n", host,rp->ai_family, rp->ai_socktype);
    }
    return 0;
}