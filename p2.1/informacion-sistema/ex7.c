#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
    if(pathconf("ex7.c",_PC_LINK_MAX) == -1) handle_error("Error in pathconf("ex7.c",_PC_LINK_MAX)");
    if(pathconf("ex7.c",_PC_PATH_MAX) == -1) handle_error("Error in pathconf("ex7.c",_PC_PATH_MAX)");
    if(pathconf("ex7.c",_PC_NAME_MAX) == -1) handle_error("Error in pathconf("ex7.c",_PC_NAME_MAX)");
   printf("Maximum number of links: %li\n",pathconf("ex7.c",_PC_LINK_MAX));
   printf("Maximum path size: %li\n",pathconf("ex7.c",_PC_PATH_MAX));
   printf("Maximum filename size: %li\n",pathconf("ex7.c",_PC_NAME_MAX));
}
