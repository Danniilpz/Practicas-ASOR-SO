#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

#define USAGE "Usage: %s command1 argument1 command2 argument2\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char * argv[]){
    if (argc != 5){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    if(pipe(pipefd) == -1) handle_error("Error in pipe()");

    pid_t pid = fork();
    switch(pid){
        case -1:
            handle_error("Error in fork()");
            break;
        case 0: //Child
            if(dup2(pipefd[0], 0) == -1) handle_error("Error in dup2()");
            close(pipefd[1]);

            if(execlp(argv[3], argv[3], argv[4], (char *) NULL) == -1) handle_error("Error in execlp()");

            close(pipefd[0]);
            break;
        case 1: //Parent
            if(dup2(pipefd[1], 1) == -1) handle_error("Error in dup2()");
            close(pipefd[0]);

            if(execlp(argv[1], argv[1], argv[2], (char *) NULL) == -1) handle_error("Error in execlp()");

            close(pipefd[1]);
            break;
    }

    return 0;
}