#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]){
    int fd=open("test",O_WRONLY);
    write(fd,argv[1],strlen(argv[1]));

}