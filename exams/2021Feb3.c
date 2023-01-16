/*
Escribe un programa que lea simultáneamente de una tubería con nombre,
que existirá previamente en el directorio actual de trabajo y se llamará tuberia , y del terminal.
● Imprimirá en el terminal los datos leídos y terminará tras 5 segundos sin recibir datos.
● Al detectar el fin de fichero en la tubería, la cerrará y volverá a abrirla.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>

#define handle_error(msg)\
    do{perror(msg);exit(EXIT_SUCCESS);}while(0);
int main(){
    //mkfifo("fifo", 0777);

    int fifo;
    if((fifo = open("fifo",O_RDONLY|O_NONBLOCK)) == -1) handle_error("Error in open()");

    fd_set rfds;
    struct timeval tv;
    int retval;

    /* Watch stdin (fd 0) to see when it has input. */

    do{
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        FD_SET(fifo, &rfds);

        tv.tv_sec = 5;
        tv.tv_usec = 0;

        if((retval = select(fifo+1, &rfds, NULL, NULL, &tv)) == -1) handle_error("error in select");

            if(FD_ISSET(STDIN_FILENO, &rfds)){
                char buf[256];
                int bytes_read= 0;
                bytes_read = read(STDIN_FILENO,&buf,256);
                write(STDOUT_FILENO, buf, bytes_read);
            }
            else if(FD_ISSET(fifo, &rfds)){
                char buf[256];
                int bytes_read= 0;
                bytes_read = read(fifo, buf, 256);
                if(bytes_read == 0){
                    close(fifo);
                    if((fifo = open("fifo",O_RDONLY|O_NONBLOCK)) == -1) handle_error("Error in open()");
                }
                else{
                    write(STDOUT_FILENO, buf, bytes_read);  
                }
            }
        else
            printf("No data within five seconds.\n");
    }while(retval !=0);
    
    return 0;
}