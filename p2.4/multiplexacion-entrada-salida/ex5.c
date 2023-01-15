#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

void read_pipe(int fd){
    char buf[256];
    int bytes_read= 0;

    do{
        bytes_read = read(fd, buf, 256);              
        write(STDOUT_FILENO, buf, bytes_read);                
    }while(bytes_read == 256);

    close(fd); 
}

int main(){
    int fd1, fd2;
    if((fd1 = open("pipe1",O_RDONLY|O_NONBLOCK,00400)) == -1) handle_error("Error in open()");
    if((fd2 = open("pipe2",O_RDONLY|O_NONBLOCK,00400)) == -1) handle_error("Error in open()");
    
    fd_set setfd;
    struct timeval tv;
    int retval;
    do{ 
        FD_ZERO(&setfd);
        FD_SET(fd1, &setfd);
        FD_SET(fd2, &setfd);

        tv.tv_usec = 0;
        tv.tv_sec = 15;

        if((retval = select(fd2+1, &setfd, NULL, NULL, &tv)) == -1) handle_error("Error in select()");

        if(FD_ISSET(fd1, &setfd)){
            read_pipe(fd1);
            if((fd1 = open("pipe1", O_RDONLY|O_NONBLOCK, 00400)) == -1) handle_error("Error in open()");
        }
        else if(FD_ISSET(fd2, &setfd)){
            read_pipe(fd2);
            if((fd2 = open("pipe2", O_RDONLY|O_NONBLOCK, 00400)) == -1) handle_error("Error in open()");
        }
    } while(retval != 0);
    return 0;
}