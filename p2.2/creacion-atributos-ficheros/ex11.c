#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <string.h>
 
int main(int argc, char *argv[]){
   struct stat inode;
   stat(argv[1],&inode);
   if(S_ISREG(inode.st_mode)){
      char name1[50];
      strcat(strcpy(name1,argv[1]),".hard");
      char name2[50];
      strcat(strcpy(name2,argv[1]),".sym");
      link(argv[1],name1);
      symlink(argv[1],name2);
   }
   return 0;

}
