#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

int main(){
    int policy; 
    if((policy = sched_getscheduler(0)) == -1) handle_error("Error in sched_getscheduler()");

    printf("Policy: ");
    switch(policy){
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        default:
            printf("ERROR\n");
            break;
    }

    
    printf("Max. priority: %d\n", sched_get_priority_max(policy));
    printf("Min priority: %d\n", sched_get_priority_min(policy));
    
    struct sched_param p;
    if(sched_getparam(0, &p) == -1) handle_error("Error in sched_getparam()");
    printf("Priority: %d\n", p.sched_priority);
}