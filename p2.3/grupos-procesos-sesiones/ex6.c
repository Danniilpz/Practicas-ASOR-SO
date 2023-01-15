#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

void print_process_info(pid_t owner){
    char type[7];
    if(owner == 0) strcpy(type,"child"); 
    else if (owner == 1) strcpy(type, "parent");

    pid_t pid = getpid();
    printf("[%s] PID: %d\n", type, pid);
    printf("[%s] PPID: %d\n", type, getppid());
    printf("[%s] PGID: %d\n", type, getpgid(pid));
    printf("[%s] SID: %d\n", type, getsid(pid));

    struct rlimit rlim;
    if(getrlimit(RLIMIT_NOFILE, &rlim) == -1) handle_error("Error in getrlimit()");
    printf("[%s] Max. number of files: %li\n", type, rlim.rlim_max);

    char buffer[100];
    if(getcwd(buffer,sizeof(buffer)) == NULL) handle_error("Error in getcwd()");
    printf("[%s] Current working directory: %s\n", type, buffer);
}

int main(){
    pid_t pid=fork();
    switch(pid){
        case -1:
            handle_error("Error in fork()");
            break;
        case 0:
            setsid();
            chdir("/tmp");
            print_process_info(0);
            sleep(5);
            break;
        case 1:
            print_process_info(1);
            sleep(15);
            break;
    }
    
    return 0;
}