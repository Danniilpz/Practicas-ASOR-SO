#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
 
int main(int argc, char *argv[]){
   int fd=open("test.txt",O_CREAT|O_WRONLY|O_TRUNC,0777);
   dup2(fd,1);
   dup2(fd,2);
   printf("prueba\n");
   perror("Error");
   return 0;
}
