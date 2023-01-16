/*
Escribe un programa servidor TCP que devuelva la dirección del cliente al
recibir cualquier mensaje. El programa se ejecutará de la siguiente manera:
$ ./tcp <dir IPv4 o IPv6 en cualquier formato> <puerto>
Por ejemplo:
$ ./tcp :: 7777
*/
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define handle_error(msg)\
    do{ perror(msg); exit(EXIT_FAILURE);}while(0);

#define handle_error_gai(code)\
    do{ fprintf(stderr, "Error: %s\n", gai_strerror(code));exit(EXIT_FAILURE);}while(0);

    
#define BUF_SIZE 500

int
main(int argc, char *argv[]){

    if (argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct addrinfo hints, *result;
    int e1, e2;
    char in[BUF_SIZE], out[NI_MAXHOST+1];
    int server, client;
    struct sockaddr_storage addr;
    socklen_t addrlen;
    char host[NI_MAXHOST], service[NI_MAXSERV];
    ssize_t nread;
    size_t nwrite;


    printf("Creating a TCP server in address %s and port %s\n", argv[1], argv[2]);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((e1 = getaddrinfo(argv[1], argv[2], &hints, &result)) == -1) handle_error_gai(e1);

    if((server = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1) handle_error("Error in socket()");

    if (bind(server, result->ai_addr, result->ai_addrlen) == -1) handle_error("Error in bind()");

    if(listen(server, 40) == -1 ) handle_error("Error in listen()");

    freeaddrinfo(result);    

    addrlen = sizeof(addr);

    while((in[0] != 'q' || in[0] != 'Q')) {

        if((client = accept(server,(struct sockaddr *) &addr, &addrlen)) == -1) handle_error("Error in accept()");
        
        if((e2 = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV)) != 0) handle_error_gai(e2)
        printf("Conexión desde %s:%s\n", host, service);

        while(1){
            if((nread = recv(client, in, BUF_SIZE, 0)) == -1) handle_error("Error in recv()");

            if(nread == 0 || nread == 2 && (in[0] == 'q' || in[0] == 'Q')) break;

            sprintf(out,"%s\n",host);
            nwrite = strlen(out);
            out[nwrite]='\0';
            if((send(client, out, nwrite, 0) == -1)) handle_error("Error in send()");
        }
        
        printf("Conexion terminada.");
    }

    close(client);
    close(server);
    printf("TCP server closed");
}