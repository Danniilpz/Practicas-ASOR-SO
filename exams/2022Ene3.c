#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define handle_error(msg)\
    do{ perror(msg); exit(EXIT_FAILURE); } while(0)

int main(int argc, char *argv[]){
    if (argc != 5) {
        fprintf(stderr, "Usage: %s command1 argument1 command2 argument2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    if(pipe(pipefd) == -1) handle_error("Error in pipe()");

    pid_t pid1, pid2;

    pid1 = fork();
    switch(pid1){
        case -1:
            handle_error("Error in fork()");
            break;
        case 0:             
            close(pipefd[1]);
            if(dup2(pipefd[0], 0) == -1) handle_error("Error in dup2()");
            close(pipefd[0]);

            if(execlp(argv[3], argv[3], argv[4], NULL) == -1) handle_error("Error in execlp()");

            break;
        default:
            pid2 = fork();
            switch(pid2){
                case -1:
                    handle_error("Error in fork()");
                    break;
                case 0:                     
                    close(pipefd[0]);
                    if(dup2(pipefd[1], 1) == -1) handle_error("Error in dup2()");
                    close(pipefd[1]);

                    if(execlp(argv[1], argv[1], argv[2], NULL) == -1) handle_error("Error in execlp()");

                    break;
                default:
                    close(pipefd[0]);
                    close(pipefd[1]);

                    int status;
                    waitpid(pid1, &status, 0);
                    printf("Child 1 - PID: %d - Status: %d\n", pid1, status);
                    waitpid(pid2, &status, 0);
                    printf("Child 2 - PID: %d - Status: %d\n", pid2, status);                    
            }
    }
    return 0;

}