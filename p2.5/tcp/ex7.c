#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define handle_error_gai(code_error) \
          do { fprintf(stderr, "Error in getaddrinfo(): %s\n", gai_strerror(code_error)); exit(EXIT_FAILURE); } while (0)
#define USAGE  "ERROR: Usage: %s [address] [port]\n"
#define MESSAGE_MAXSIZE 200

int main(int argc,char **argv){

    if(argc != 3){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct addrinfo hints, *dest_addr = NULL; //for getaddrinfo()
    struct sockaddr_storage src_addr;
    int e1, e2, e3; //error codes
    ssize_t bytes_read; //for recv()
    size_t bytes_write; //for sendto()
    char msg[MESSAGE_MAXSIZE]; //for sendto()

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((e1 = getaddrinfo(argv[1], argv[2], &hints, &dest_addr)) == -1) handle_error_gai(e1);

    if((e2 = socket(dest_addr->ai_family, dest_addr->ai_socktype, dest_addr->ai_protocol)) == -1) handle_error("Error in socket()");

    if((e3 = connect(e2,(struct sockaddr *)dest_addr->ai_addr, dest_addr->ai_addrlen)) == -1) handle_error("Error in connect()");

    freeaddrinfo(dest_addr); //no longer needed

    while(1){
        
        bytes_write=read(STDIN_FILENO,&msg,MESSAGE_MAXSIZE-1);
        msg[bytes_write] = '\0';    
        if( (send(e2, &msg, bytes_write, 0)) == -1) handle_error("Error in send()");

        if(bytes_write == 2 && (msg[0] == 'q'||msg[0] == 'Q')){
            printf("Conexión terminada\n");
            break;
        }

        if( (bytes_read = recv(e2, msg, MESSAGE_MAXSIZE, 0)) == -1) handle_error("Error in recv()");
        msg[bytes_read] = '\0';
        printf("Server says: %s\n", msg);

    }

    close(e2);

    return 0;
}
