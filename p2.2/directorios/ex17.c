#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
 
int main(int argc, char * argv[]){
   struct stat inode,inode2;
   stat(argv[1],&inode);
   if(S_ISDIR(inode.st_mode)){
        DIR *direc=opendir(argv[1]);
        struct dirent *sig;
        double size=0;
        while((sig=readdir(direc))!=NULL){
            char *name=sig->d_name;
            char name2[100];
            strcpy(name2,argv[1]);
            strcat(name2,"/");
            strcat(name2,name);
            lstat(name2,&inode2);
            //printf("%s\n",name);
            if(S_ISREG(inode2.st_mode)){
                if((inode2.st_mode&(S_IXUSR|S_IXGRP|S_IXOTH))){
                    size+=inode2.st_size;
                    printf("%s",name);
                    printf("   *\n");
                }
                
            }
            else if(S_ISDIR(inode2.st_mode)){
                printf("%s",name);
                printf("/\n");
            }
            else if(S_ISLNK(inode2.st_mode)){                
                printf("%s   ->    ",name);
                char buf[200];
                readlink(&name2,&buf,300);
                printf("%s\n",buf);
            }
        }
        size/=1000;
        printf("%f KB\n",size);
        closedir(direc);
        
   }
   return 0;

}
