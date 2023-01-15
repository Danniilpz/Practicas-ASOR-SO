#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)


int main(){
    if(setenv("SLEEP_SECS", "15", 1) == -1) handle_error("Error in setenv()");

    sigset_t blk_set;
    if(sigemptyset(&blk_set) == -1) handle_error("Error in sigemptyset()");
    if(sigaddset(&blk_set, SIGINT) == -1) handle_error("Error in sigaddset()");	
    if(sigaddset(&blk_set, SIGTSTP) == -1) handle_error("Error in sigaddset()");	

    if(sigprocmask(SIG_BLOCK, &blk_set, NULL) == -1) handle_error("Error in sigprocmask()");

    char *sleep_secs;
    if((sleep_secs = getenv("SLEEP_SECS")) == NULL) throw_error("SLEEP_SECS env variable not exists");

    sleep(atoi(sleep_secs));

    sigset_t blk_pending;
    if(sigpending(&blk_pending) == -1) handle_error("Error in sigpending()");
    if(sigismember(&blk_pending, SIGINT) == 1){
        sigdelset(&blk_set, SIGINT);
    }
    else{
       printf("SIGINT not received"); 
    } 
    if(sigismember(&blk_pending,SIGTSTP) == 1){	
        sigdelset(&blk_set, SIGTSTP);
    }
    else{
       printf("SIGTSTP not received"); 
    } 
    
    sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

    printf("Ending program\n");

    return 0;
}