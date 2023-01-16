/*
Escribe un programa que ejecute dos comandos de la siguiente forma:
● Los comandos serán el primer y segundo argumento del programa. El resto de argumentos
del programa se considerarán argumentos del segundo comando:
$ ./conecta comando1 comando2 arg2_1 arg2_2 ...
● Cada comando se ejecutará en un proceso distinto, que imprimirá su PID por el terminal.
● El programa conectará la salida estándar del primer proceso con la entrada estándar del
segundo, y esperará la finalización de ambos para terminar su ejecución.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg)\
    do{ perror(msg); exit(EXIT_FAILURE);}while(0);

int main(int argc, char *argv[]){

    if (argc < 3) {
        fprintf(stderr, "Usage: %s comando1 comando2 arg2_1 arg2_2 ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd[2];
    pid_t pid;
    char *argv2[argc-2];

    if(pipe(pipefd) == -1)handle_error("error in pipe");
    
    pid = fork();
    switch(pid){
        case -1:
            handle_error("error in fork");
            break;
        case 0:
            printf("Hijo: %d\n",getpid());
            close(pipefd[1]);
            if((dup2(pipefd[0],0)) == -1) handle_error("error in dup2");
            close(pipefd[0]);

            for(int i=2;i<argc;i++){
                argv2[i]=argv[i];
            }

            if(execvp(argv[2],argv2) == -1) handle_error("error in execvp");

            

            break;
        default:
            printf("Padre: %d\n",getpid());
            close(pipefd[0]);
            if((dup2(pipefd[1],1)) == -1) handle_error("error in dup2");
            close(pipefd[1]);

            if(execlp(argv[1],argv[1],NULL) == -1) handle_error("error in execlp");

            
            int status;
            wait(&status);
            

            break;

    }    
}