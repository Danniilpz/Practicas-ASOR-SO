#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <time.h>

#define handle_error_gai(code_error, msg) \
          do { fprintf(stderr, "Code error: %d msg: %s\n", code_error, gai_strerror(code_error)); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MAX_HOST 200

#define USAGE  "ERROR: Usage: %s [address] [port]\n"

int main(int argc,char **argv){
    if(argc != 3){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }
    /*char addr[MAX_HOST], host[MAX_HOST], buf[80], serv[MAX_HOST];
    
    struct addrinfo *res = NULL;
    int sc, s, nread, addrlen;*/
    
    struct addrinfo hints;
    int e1, e2; //error codes

    printf("Creating an UDP server in address %s and port %s", argv[1], argv[2]);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //Both IPv4 and IPv6
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if((e1 = getaddrinfo(argv[1], argv[2], &hints, &res)) == -1) handle_error_gai(e1, "Error in getaddrinfo()");

    freeaddrinfo(res); //no longer needed

    if((e2 = socket(res->ai_family, res->ai_socktype, res->ai_protocol) == -1) handle_error("Error in socket()");

    
    bind(sc, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
    while(1){
        addrlen = sizeof(addr);
        int c = recvfrom(sc, buf, 80, 0, (struct sockaddr *) &addr, &addrlen);
        getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST,
        serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
        printf("Recibidos %d bytes de %s:%s\n", c, host, serv);
        sendto(sc, buf, c, 0, (struct sockaddr *) &addr, addrlen);


    }
}