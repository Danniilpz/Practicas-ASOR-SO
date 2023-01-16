/*
Escribe un programa servidor UDP que escuche peticiones realizadas a una
dirección (IPv4 o IPv6 en cualquier formato) y puerto dados como argumentos. El servidor
devolverá la hora (en formato HH:MM:SS) al recibir cualquier mensaje. En cada mensaje, el servidor
mostrará la dirección y el puerto del cliente.
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

º
#define handle_error_gai(s)\
    do{fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));exit(EXIT_FAILURE);} while(0);
#define BUF_SIZE 500

int main(int argc, char *argv[]){
    struct addrinfo hints;
    struct addrinfo *rp;
    int sfd, s;
    struct sockaddr_storage addr;
    socklen_t addrlen;
    ssize_t nread;
    char in[BUF_SIZE],out[BUF_SIZE];
    char host[NI_MAXHOST], service[NI_MAXSERV];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

    if((s = getaddrinfo(argv[1], argv[2], &hints, &rp)) == -1) handle_error_gai(s);
    
    if((sfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol)) == -1) handle_error("error in socket");
    
    if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == -1) handle_error("error in bind");

    freeaddrinfo(rp);     

    addrlen = sizeof(addr);

    while(1) {
        printf("Esperando conexiones UDP...\n");

        if((nread = recvfrom(sfd, in, BUF_SIZE, 0, (struct sockaddr *) &addr, &addrlen)) == -1) handle_error("error in recvfrom");

        if((s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV)) == -1) handle_error_gai(s);

        printf("Received msg from %s:%s\n", host, service);

        time_t t = time(NULL);
        strftime(out,BUF_SIZE,"%H:%M:%S\n",localtime(&t));

        if (sendto(sfd, out, strlen(out), 0, (struct sockaddr *) &addr,addrlen) == -1) handle_error("error in sendto");
    }
}