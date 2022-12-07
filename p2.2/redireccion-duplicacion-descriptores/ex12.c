#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
 
int main(int argc, char *argv[]){
   int fd=open("test.txt",O_CREAT|O_WRONLY,0777);
   dup2(fd,1);
   printf("prueba\n");
   return 0;

}
