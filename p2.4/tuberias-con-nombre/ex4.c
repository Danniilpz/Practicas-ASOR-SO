#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define USAGE "Usage: %s pipe_content\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char * argv[]){
    if (argc < 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    mkfifo("test", 0777);

    int fd;
    if((fd = open("test",O_WRONLY)) == -1) handle_error("Error in open()");

    write(fd, argv[1], strlen(argv[1]));

    close(fd);
    return 0;
}