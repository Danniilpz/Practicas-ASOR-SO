#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

int main(){
    pid_t pid = getpid();
    printf("PID: %d\n", pid);
    printf("PPID: %d\n", getppid());
    printf("PGID: %d\n", getpgid(pid));
    printf("SID: %d\n", getsid(pid));

    struct rlimit rlim;
    if(getrlimit(RLIMIT_NOFILE, &rlim) == -1) handle_error("Error in getrlimit()");
    printf("Max. number of files: %li\n", rlim.rlim_max);

    char buffer[100];
    if(getcwd(buffer,sizeof(buffer)) == NULL) handle_error("Error in getcwd()");
    printf("Current working directory: %s\n", buffer);

    return 0;
}