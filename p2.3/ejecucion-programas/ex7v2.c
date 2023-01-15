#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

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

    int len = 1;
    for (int i = 1; i < argc; i++){
        len += strlen(argv[i]) + 1;
    }        
    char *command = malloc(sizeof(char)*len);
    strcpy(command, "");

    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    if(system(command) == -1) handle_error("Error in system()");
    
    printf("El comando terminó de ejecutarse\n");
    
    return 0;
}