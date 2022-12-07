#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 

int main(int argc, char * argv[]){
    
    execvp(argv[1], argv+1);
    
    /*system(argv[1]);*/
    printf("El comando terminó de ejecutarse\n");
    
    return 0;
}