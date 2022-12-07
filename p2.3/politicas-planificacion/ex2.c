#include <sched.h>
#include <stdio.h>
int main(){
    int policy=sched_getscheduler(0);
    printf("Planificación: ");
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
    }
    struct sched_param p;
    sched_getparam(0,&p);
    printf("Prioridad: %d\n",p.sched_priority);
    printf("Prioridad max: %d\n",sched_get_priority_max(policy));
    printf("Prioridad min: %d\n",sched_get_priority_min(policy));
}