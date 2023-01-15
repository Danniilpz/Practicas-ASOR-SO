#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(){

    int fd;
    //open("test1.c",O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH|S_IXOTH);    
    if(fd = open("test1.c", O_CREAT, 0645)) == -1) handle_error("Error creating a file");
    close(fd);

    return 0;
}