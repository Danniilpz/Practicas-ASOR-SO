#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <stdlib.h>
#include <time.h>

#define USAGE "Usage: %s path\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]){

   if (argc != 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
   }

   struct stat inode;
   if(stat(argv[1],&inode) == -1) handle_error("Error in stat()");

   printf("Major number:\t\t%d\n",major(inode.st_dev));
   printf("Minor number:\t\t%d\n",minor(inode.st_dev));
   printf("I-node:\t\t\t%lu\n",inode.st_ino);

   printf("File type:\t\t");
   mode_t mode = inode.st_mode;
   if (S_ISLNK(mode)){
		printf("Symbolic link");
	} else if (S_ISREG(mode)) {
		printf("Regular file");
	} else if (S_ISDIR(mode)) {
		printf("Directory");
	} else {
      printf("Other");
   }
   printf("\n");

   printf("Last file access:\t%s",ctime(&inode.st_atime));
   printf("Last file modification:\t%s",ctime(&inode.st_mtime));
   printf("Last status change:\t%s",ctime(&inode.st_ctime));
 
   return 0;
}
