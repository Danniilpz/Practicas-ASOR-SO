#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h>

#define USAGE "Usage: %s command\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)


int main(int argc, char * argv[]){
    if (argc < 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }

    if(execvp(argv[1], argv + 1) == -1) handle_error("Error in execvp()");
    
    /*system(argv[1]);*/
    printf("El comando terminó de ejecutarse\n");
    
    return 0;
}