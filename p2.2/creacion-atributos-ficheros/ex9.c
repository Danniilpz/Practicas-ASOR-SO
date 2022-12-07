#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/sysmacros.h>
 
 
int main(int argc, char *argv[]){
   struct stat inode;
   stat(argv[1],&inode);
   printf("%d\n",major(inode.st_dev));
   printf("%d\n",minor(inode.st_dev));
   printf("%d\n",inode.st_ino);
   printf("%d\n",inode.st_mode);
   printf("%d\n",inode.st_atime);
 
   return 0;
}
