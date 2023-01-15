#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define USAGE "Usage: %s command\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

void redirect(char *path, int stream_old){
    int stream;
    if((stream=open(path,O_CREAT|O_RDWR|O_TRUNC,0777)) == -1) handle_error("Error in open()");

    if(dup2(stream, stream_old) == -1) handle_error("Error in dup2()");
}

int main(int argc, char * argv[]){
    if (argc < 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    switch(pid){
        case -1:
            handle_error("Error in fork()");
            break;
        case 0:
            printf("[Child] Process %i (Parent %i)", getpid(), getppid());
            setsid();

            redirect("/dev/null",0);
            redirect("/tmp/daemon.out",1);
            redirect("/tmp/daemon.err",2);

            if(execvp(argv[1], argv + 1) == -1) handle_error("Error in execvp()");
            break;
        case 1:
            printf("[Parent] Process %i (Parent %i)", getpid(), getppid());
            break;
    }
    
    return 0;
}