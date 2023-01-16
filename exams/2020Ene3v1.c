/*
Escribe un programa que lea simultáneamente de dos tuberías con nombre
(tuberia1 y tuberia2). El programa mostrará el nombre de la tubería desde la que se leyó y los
datos leídos. El programa detectará cuándo se cierra el extremo de escritura de una tubería ( read()
devuelve 0) para cerrarla y volver a abrirla.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define handle_error(msg)\
    do{perror(msg); exit(EXIT_FAILURE); }while(0);

int main(void) {
    fd_set rfds;
    struct timeval tv;
    int retval, nread;
    int fd1, fd2;
    char buf[256];

    //mkfifo("tuberia1",0777);
    //mkfifo("tuberia2",0777);

    if((fd1 = open("tuberia1",O_RDONLY|O_NONBLOCK,00400)) == -1) handle_error("error in open");
    if((fd2 = open("tuberia2",O_RDONLY|O_NONBLOCK,00400)) == -1) handle_error("error in open");

    do{
        FD_ZERO(&rfds);
        FD_SET(fd1, &rfds);
        FD_SET(fd2, &rfds);

        tv.tv_sec = 5;
        tv.tv_usec = 0;

        if((retval = select(fd2+1, &rfds, NULL, NULL, &tv)) == -1) handle_error("Error in select");

        if(FD_ISSET(fd1, &rfds)){
            if((nread = read(fd1, buf, 256)) == -1) handle_error("error in read");

            if(nread == 0){
                close(fd1);
                if((fd1 = open("tuberia1",O_RDONLY|O_NONBLOCK)) == -1) handle_error("Error in open()");
            }
            else{
                char out[nread+12];
                strcpy(out,"tuberia 1: ");
                strcat(out,buf);
                strcat(out,"\n");
                write(STDOUT_FILENO, out, strlen(out));  
                //fprintf("tuberia1: %s",buf);
            }

        } 
        else if(FD_ISSET(fd2, &rfds)){
            if((nread = read(fd2, buf, 256)) == -1) handle_error("error in read");

            if(nread == 0){
                close(fd2);
                if((fd2 = open("tuberia2",O_RDONLY|O_NONBLOCK)) == -1) handle_error("Error in open()");
            }
            else{
                char out[nread+12];
                strcpy(out,"tuberia 2: ");
                strcat(out,buf);
                strcat(out,"\n");
                write(STDOUT_FILENO, out, strlen(out));  
                //fprintf("tuberia2: %s",buf);
            }
        }

    } while (retval != 0);
    exit(EXIT_SUCCESS);
}