#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    setenv("SLEEP_SECS","15",1);
    sigset_t blk_set;
    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGINT);	
    sigaddset(&blk_set, SIGTSTP);	
    sigprocmask(SIG_BLOCK, &blk_set, NULL);
    sleep(atoi(getenv("SLEEP_SECS")));
    sigset_t blk_pending;
    sigpending(&blk_pending);
    if(sigismember(&blk_pending,SIGINT)==1){
        sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
    }
    else if(sigismember(&blk_pending,SIGTSTP)==1){	
        sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
    }
    printf("Termina la ejecución\n");

    return 0;
}