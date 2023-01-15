#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define USAGE "Usage: %s directory\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)
 
int main(int argc, char * argv[]){
    if (argc != 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat inode;
    if(stat(argv[1],&inode) == -1) handle_error("Error in stat()");

    if(!S_ISDIR(inode.st_mode)) throw_error("The path is not a directory");

    if((DIR *direc = opendir(argv[1])) == NULL) handle_error("Error in opendir()");

    struct dirent *current;
    double size = 0;
    while((current = readdir(direc)) != NULL){
        char *name = current->d_name;

        char pathname[100];
        strcpy(pathname, argv[1]);
        strcat(pathname, "/");
        strcat(pathname, name);
        
        if(lstat(pathname, &inode) == -1) handle_error("Error in lstat()");
        
        if(S_ISREG(inode.st_mode)){
            if((inode.st_mode & (S_IXUSR|S_IXGRP|S_IXOTH))){
                size += inode.st_size;
                printf("%s   *\n", name);
            }            
        }
        else if(S_ISDIR(inode.st_mode)){
            printf("%s/\n", name);
        }
        else if(S_ISLNK(inode.st_mode)){                
            printf("%s   ->    ",name);

            char buf[200];
            readlink(&pathname, &buf, 300);

            printf("%s\n", buf);
        }
        else{
            printf("%s\n", name);
        }
    }

    size/=1000;
    printf("%f KB\n",size);

    closedir(direc);   

    return 0;
}
