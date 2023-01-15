#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define USAGE "Usage: %s path\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)
 
int main(int argc, char *argv[]){
   
   if (argc != 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
   }

   int fd;
   if ((fd = open("test.txt",O_CREAT|O_WRONLY,0777)) == -1) handle_error("Error creating a file");

   if (dup2(fd,1) == -1){
      handle_error("Error in dup2()");
      close(fd);
   } 
   
   write(1, "prueba\n", 7);
   printf("prueba\n");

   close(fd);

   return 0;

}
