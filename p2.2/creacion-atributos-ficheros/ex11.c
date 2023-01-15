#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define USAGE "Usage: %s path_to_a_regular_file\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)
 
int main(int argc, char *argv[]){

   if (argc != 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
   }

   struct stat inode;
   if(stat(argv[1],&inode) == -1) handle_error("Error in stat()");

   if(!S_ISREG(inode.st_mode)) throw_error("File is not a regular file");
   
   char name1[50];
   strcat(strcpy(name1, argv[1]), ".hard");
   char name2[50];
   strcat(strcpy(name2, argv[1]), ".sym");

   if(link(argv[1],name1) == -1) handle_error("Error creating a link");

   if(symlink(argv[1],name2) == -1) handle_error("Error creating a symbolic link");

   return 0;

}
