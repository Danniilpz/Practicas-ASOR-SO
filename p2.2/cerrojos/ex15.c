#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
    int fd=open("test15.txt",O_CREAT,0777);
    if(lockf(fd,F_LOCK,0)){
        sleep(10);
        lockf(fd,F_ULOCK,0);
        sleep(10);
    }
    else{
        perror("Error");
    }
}