#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
    pid_t proceso=fork();
    if(proceso==0){
        setsid();
        int fd0=open("/dev/null",O_CREAT|O_RDWR|O_TRUNC,0777);
        int fd1=open("/tmp/daemon.out",O_CREAT|O_RDWR|O_TRUNC,0777);
        int fd2=open("/tmp/daemon.err",O_CREAT|O_RDWR|O_TRUNC,0777);
        dup2(fd0,0);
        dup2(fd1,1);
        dup2(fd2,2);
        execvp(argv[1], argv+1);        
    }
        
    return 0;
}