#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
    if(sysconf(_SC_ARG_MAX) == -1) handle_error("Error in sysconf(_SC_ARG_MAX)");
    if(sysconf(_SC_CHILD_MAX) == -1) handle_error("Error in sysconf(_SC_CHILD_MAX)");
    if(sysconf(_SC_OPEN_MAX) == -1) handle_error("Error in sysconf(_SC_OPEN_MAX)");

    printf("Maximum number of arguments: %d\n",sysconf(_SC_ARG_MAX));
    printf("Maximum number of childs: %d\n",sysconf(_SC_CHILD_MAX));
    printf("Maximum number of open files: %d\n",sysconf(_SC_OPEN_MAX));
}
