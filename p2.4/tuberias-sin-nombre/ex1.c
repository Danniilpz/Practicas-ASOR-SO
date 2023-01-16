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
            close(pipefd[1]);
            if((dup2(pipefd[0], STDIN_FILENO)) == -1) handle_error("Error in dup2()");
            close(pipefd[0]);

            if((execlp(argv[3], argv[3], argv[4], NULL)) == -1) handle_error("Error in execlp()");

            break;
        default: //Parent
            close(pipefd[0]);
            if((dup2(pipefd[1], STDOUT_FILENO)) == -1) handle_error("Error in dup2()");
            close(pipefd[1]);

            if((execlp(argv[1], argv[1], argv[2], NULL)) == -1) handle_error("Error in execlp()");

            break;
    }

    return 0;
}