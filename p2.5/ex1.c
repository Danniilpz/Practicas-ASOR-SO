#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    struct addrinfo hints;
    struct addrinfo *res, *rp;
    char host[200];
    int s;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    s = getaddrinfo(argv[1], NULL, &hints, &res);
    if(s != 0) {
        fprintf(stderr, "Error getaddrinfo(): %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }
    for(rp=res; rp!=NULL; rp=rp->ai_next){
        getnameinfo(rp->ai_addr, rp->ai_addrlen, host, 200, NULL, 0, NI_NUMERICHOST);
        printf("%s\t%d\t%d\n", host,rp->ai_family, rp->ai_socktype);
    }
    return 0;
}