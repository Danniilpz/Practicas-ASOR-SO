#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>


int main(){
    printf("PID: %d\n",getpid());
    printf("PPID: %d\n",getppid());
    printf("PGID: %d\n",getpgid(getpid()));
    printf("SID: %d\n",getsid(getpid()));
    struct rlimit rlim;
    getrlimit(RLIMIT_NOFILE,&rlim);
    printf("Num max ficheros: %li\n",rlim.rlim_max);
    char buffer[100];
    getcwd(&buffer,100);
    printf("Directorio actual: %s\n",buffer);
    return 0;
}