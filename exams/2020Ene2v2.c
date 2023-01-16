/*
Escribe un programa servidor TCP que escuche en una dirección (IPv4 o IPv6
en cualquier formato) y puerto dados como argumentos. El servidor devolverá lo que el cliente le
envíe. En cada conexión, el servidor mostrará la dirección y el puerto del cliente.
*/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


#define handle_error(msg)\
    do{perror(msg); exit(EXIT_FAILURE); }while(0);
#define handle_error_gai(msg,s)\
    do{fprintf(stderr, "%s: %s\n", msg, gai_strerror(s)); exit(EXIT_FAILURE);}while(0);
#define BUF_SIZE 500

int
main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints;
    struct addrinfo *rp;
    int sfd, client, s;
    struct sockaddr_storage addr;
    socklen_t addrlen;
    ssize_t nread;
    char buf[BUF_SIZE];
    char host[NI_MAXHOST], service[NI_MAXSERV];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

    if((s = getaddrinfo(argv[1], argv[2], &hints, &rp)) == -1) handle_error_gai("error in getaddrinfo",s);

    if((sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) handle_error("error in socket");

    if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == -1) handle_error("error in bind");

    if(listen(sfd, 40) == -1) handle_error("error in listen");

    freeaddrinfo(rp);           

    addrlen = sizeof(addr);

    while(1) {
        if((client = accept(sfd, (struct sockaddr *) &addr, &addrlen)) == -1) handle_error("error in connect");

        if((s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV)) != 0) handle_error_gai("error in getnameinfo",s);
        
        printf("Connection from %s:%s\n", host, service);

        while(1){
            if((nread = recv(client, buf, BUF_SIZE, 0)) == -1) handle_error("error in recv");
                   
            buf[nread]='\0';

            if (send(client, buf, nread, 0) == -1) handle_error("error in send");
        }
        printf("Conexión terminada\n");
        
    }
    close(sfd);
    close(client);
}