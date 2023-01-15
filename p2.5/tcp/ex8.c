#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <time.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error_gai(code_error) \
          do { fprintf(stderr, "Error in getaddrinfo(): %s\n", gai_strerror(code_error)); exit(EXIT_FAILURE); } while (0)
#define USAGE  "ERROR: Usage: %s [address] [port]\n"
#define HELP "\nOption no recognized.\nHelp: option+enter\nOptions:\n\t 't' return the hour\n\t 'd' return the date\n\t 'q' end service\n:"
#define MESSAGE_MAXSIZE 200


int main(int argc,char **argv){

    if(argc != 3){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct addrinfo hints, *res = NULL; //for getaddrinfo()
    struct sockaddr_storage addr;
    int e1, e2, e3; //error codes
    int client; //for accept()
    socklen_t addrlen; //for recv()
    ssize_t bytes_read; //for recv()
    size_t bytes_write; //for sendto()
    char host[NI_MAXHOST], serv[NI_MAXSERV]; //for getnameinfo()
    char msg[MESSAGE_MAXSIZE]; //for sendto()+
    pid_t pid;

    printf("Creating a TCP server in address %s and port %s\n", argv[1], argv[2]);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((e1 = getaddrinfo(argv[1], argv[2], &hints, &res)) == -1) handle_error_gai(e1);

    if((e2 = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) handle_error("Error in socket()");

    if((bind(e2, (struct sockaddr *) res->ai_addr, res->ai_addrlen)) == -1) handle_error("Error in bind()");

    if(listen(e2, 40) == -1 ) handle_error("Error in listen()");

    freeaddrinfo(res); //no longer needed
    
    addrlen = sizeof(addr);

    while(1){
        if( (client = accept(e2, (struct sockaddr *) &addr, &addrlen)) == -1) handle_error("Error in accept()");
        
        if((pid = fork()) == -1 ) handle_error("Error in fork()");

        if(pid == 0){

            if((e3 = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV)) != 0) handle_error_gai(e3,"Error in getnameinfo()");
            
            printf("Conexión desde %s:%s\n", host, serv);
            while(1){
                if((bytes_read = recv(client, msg, MESSAGE_MAXSIZE, 0)) == -1) handle_error("Error in recv()");
                
                if(bytes_read == 0 || (bytes_read == 2 && (msg[0] == 'q'||msg[0] == 'Q'))) break; //if client has closed or sent a Q, connection finished

                msg[bytes_read] = '\0';

                if( (send(client, msg, bytes_read, 0)) == -1) handle_error("Error in send()");
            } 
            printf("Conexión desde %s:%s terminada\n", host, serv);
            close(client);
        }
        else{
            close(client);
        }
    } 
    close(client);
    close(e2);
    printf("TCP server in address %s and port %s closed\n", argv[1], argv[2]);

    return 0;
}
