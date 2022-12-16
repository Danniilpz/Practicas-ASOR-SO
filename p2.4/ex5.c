#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void readPipe(int fd){
    char buf[256];
    int bytesRead= 0;
    do{
        bytesRead=read(fd,buf,256);              
        write(STDOUT_FILENO,buf,bytesRead);                
    }while(bytesRead==256);
    close(fd); 
}

int main(){
    int fd1=open("pipe1",O_RDONLY|O_NONBLOCK,00400);
    int fd2=open("pipe2",O_RDONLY|O_NONBLOCK,00400);
    fd_set setfd;
    struct timeval time;
    int n;
    do{ 
        FD_ZERO(&setfd);
        FD_SET(fd1,&setfd);
        FD_SET(fd2,&setfd);
        time.tv_usec=0;
        time.tv_sec=15;
        n=select(fd2+1,&setfd,NULL,NULL,&time);
        if(FD_ISSET(fd1,&setfd)){
            readPipe(fd1);
            fd1=open("pipe1",O_RDONLY|O_NONBLOCK,00400);
        }
        else if(FD_ISSET(fd2,&setfd)){
            readPipe(fd2);
            fd2=open("pipe2",O_RDONLY|O_NONBLOCK,00400);
        }
    } while(n!=0);
    return 0;
}