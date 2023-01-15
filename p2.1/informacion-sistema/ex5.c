#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {

    struct utsname info;
    if( uname(&info) == -1) handle_error("Error in uname");

    printf("sysname: %s\n",info.sysname);
    printf("nodename: %s\n",info.nodename);
    printf("release: %s\n",info.release);
    printf("version: %s\n",info.version);
    printf("machine: %s\n",info.machine);

}
