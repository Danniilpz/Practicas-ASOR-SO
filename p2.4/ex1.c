#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    int pipefd[2];
    pipe(pipefd);
    pid_t pid=fork();
    if(pid==0){
        dup2(pipefd[0],0);
        close(pipefd[1]);
        char command[100];
        strcpy(command,argv[3]);
        strcat(command," ");
        strcat(command,argv[4]);
        system(command);
        close(pipefd[0]);
    }
    else{
        dup2(pipefd[1],1);
        close(pipefd[0]);
        char command[100];
        strcpy(command,argv[1]);
        strcat(command," ");
        strcat(command,argv[2]);    
        system(command);    
        close(pipefd[1]);
    }
    return 0;
}