#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

struct sigaction act;
void handler(int signal){    
    sigset_t blk_set;
    sigemptyset(&blk_set);
    sigaddset(&blk_set, signal);	
    sigsuspend(&blk_set); 
}

int main(int argc, char * argv[]){
    act.sa_handler=(void*)handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=SA_SIGINFO;
    sigaction(SIGUSR1,&act,NULL);
    int secs=atoi(argv[1]);
    sleep(secs);
    unlink(argv[0]);
}
