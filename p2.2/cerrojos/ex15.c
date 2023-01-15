#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

int main(){
    int fd;
    if ((fd = open("test15.txt",O_CREAT|O_RDWR,0777)) == -1) handle_error("Error creating a file");

    if(lockf(fd,F_LOCK,0) == -1){
        close(fd);
        handle_error("Error locking a file");
    }
    
    time_t t;
    if( (t = time(NULL)) == -1) handle_error("Error in time()");

    printf("%s", ctime(&t));
    sleep(10);

    lockf(fd,F_ULOCK,0);
    sleep(10);
    close(fd);
}