#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define USAGE "Usage: %s seconds\n"
#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

void handler(int signal){    
    sigset_t blk_set;
    if(sigemptyset(&blk_set) == -1) handle_error("Error in sigemptyset()");
    if(sigaddset(&blk_set, signal) == -1) handle_error("Error in sigaddset()");	

    sigsuspend(&blk_set); 
}

int main(int argc, char * argv[]){
    if (argc < 2){
        fprintf(stderr, USAGE, argv[0]);
        exit(EXIT_FAILURE);
    }
    if(argv[1] == 0) throw_error("seconds must be greater than 0");

    struct sigaction act;    
    act.sa_handler = (void*) handler;
    act.sa_flags = SA_SIGINFO;

    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1,&act,NULL);

    int secs = atoi(argv[1]);
    sleep(secs);

    if(unlink(argv[0]) == -1) handle_error("Error in unlink()");
}
