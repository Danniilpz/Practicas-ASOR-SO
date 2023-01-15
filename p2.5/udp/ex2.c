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

int get_time(char *buf, char format[]){
    time_t t;
    struct tm *tmp;
    int e; //error code

    t = time(NULL);
    if((tmp = localtime(&t))== NULL) handle_error("Error in localtime()");

    if ((e = strftime(buf, MESSAGE_MAXSIZE, format, tmp)) == 0) {
        fprintf(stderr, "strftime returned 0");
        exit(EXIT_FAILURE);
    }

    return e;

}

int main(int argc,char **argv){

    if(argc != 3){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct addrinfo hints, *res = NULL; //for getaddrinfo()
    struct sockaddr_storage addr;
    int e1, e2, e3; //error codes
    socklen_t addrlen; //for recvfrom()
    ssize_t bytes_read; //for recvfrom()
    size_t bytes_write; //for sendto()
    char host[NI_MAXHOST], serv[NI_MAXSERV], buf[3]; //for getnameinfo()
    char msg[MESSAGE_MAXSIZE]; //for sendto()

    printf("Creating an UDP server in address %s and port %s\n", argv[1], argv[2]);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; //both IPv4 and IPv6
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if((e1 = getaddrinfo(argv[1], argv[2], &hints, &res)) == -1) handle_error_gai(e1);

    if((e2 = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) handle_error("Error in socket()");

    if((bind(e2, (struct sockaddr *) res->ai_addr, res->ai_addrlen)) == -1) handle_error("Error in bind()");

    freeaddrinfo(res); //no longer needed
    
    addrlen = sizeof(addr);

    do{
        if( (bytes_read = recvfrom(e2, buf, 2, 0, (struct sockaddr *) &addr, &addrlen)) == -1) handle_error("Error reading from client");

        if((e3 = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV)) != 0) handle_error_gai(e3,"Error in getnameinfo()");
        
        printf("%li bytes received from %s:%s\n", bytes_read, host, serv);

        switch(buf[0]){
            case 'q':
                printf("Closing server...\n");
                bytes_write = 14;
                sprintf(msg, "Server closed\n");
                break;

            case 't':
                bytes_write = get_time(msg, "%T %p\n");
                break;

            case 'd':
                bytes_write = get_time(msg, "%Y-%m-%d\n");
                break;      

            default:             
                printf("Command '%c' not supported\n", buf[0]);
                bytes_write = sizeof(HELP);
                sprintf(msg, "%s", HELP);
               break;
        }
        if( (sendto(e2, msg, bytes_write, 0, (struct sockaddr *) &addr, addrlen)) == -1) handle_error("Error in sendto()");

    } while(buf[0] != 'q');

    close(e2);
    printf("UDP server in address %s and port %s closed\n", argv[1], argv[2]);

    return 0;
}
