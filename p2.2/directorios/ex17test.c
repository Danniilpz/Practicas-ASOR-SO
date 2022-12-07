#include <stdio.h>
#include <sys/stat.h>
#include<sys/types.h>
#include<dirent.h>                                                                                                 
#include <unistd.h>  
#include <string.h>  
int main(int argc, char * argv[]){
	
	struct stat st;
	stat(argv[1], &st);
	if(S_ISDIR(st.st_mode)){
		DIR *directory = opendir(argv[1]);
		struct dirent* entries;
		long size = 0;
		while((entries = readdir(directory)) != NULL){
			char direc[100];
			strcpy(direc,argv[1]);
			strcat(direc,entries -> d_name);
			stat(direc, &st);
			size = size + st.st_size;
			if(entries -> d_type == DT_REG){
				if(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)){
					printf("%s",entries -> d_name);
					printf("%s\n", "    *");
				}
				else{
					printf("%s\n",entries -> d_name);
				}
			}
			else if(entries -> d_type == DT_DIR){
				printf("%s",entries -> d_name);
				printf("%s\n", "    /");
			}
			else if(entries -> d_type == DT_LNK){
				printf("%s",entries -> d_name);
				printf("%s", "    ->");
				char buf[200];
				readlink(&direc, &buf, 300); 
				printf("%s\n",buf);
			}
			else{
				printf("%s\n",entries -> d_name);
			}
			
		
		}
		
		closedir(directory);
		printf("Size : %ld\n",size);
	
	}
	else{
		perror("No es directorio");
	}
	return 0;
}
