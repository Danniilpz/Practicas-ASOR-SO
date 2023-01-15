#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
    
    if(geteuid() == -1 || getuid == -1) handle_error("Error");

    printf("Real UID: %li\n",getuid());
    printf("Effective UID: %li\n",geteuid());

    //if UID and EUID are different, setuid bit must be 1

    return 1;
}
