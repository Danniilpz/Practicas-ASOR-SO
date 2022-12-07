#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){
    pid_t proceso=fork();
    if(proceso==0){
        setsid();
        chdir("/tmp");
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
        sleep(5);
    }
    else{
        printf("PID padre: %d\n",getpid());
        printf("PPID padre: %d\n",getppid());
        printf("PGID padre: %d\n",getpgid(getpid()));
        printf("SID padre: %d\n",getsid(getpid()));
        struct rlimit rlim;
        getrlimit(RLIMIT_NOFILE,&rlim);
        printf("Num max ficheros padre: %li\n",rlim.rlim_max);
        char buffer[100];
        getcwd(&buffer,100);
        printf("Directorio actual padre: %s\n",buffer);
        sleep(15);
    }
    
    return 0;
}