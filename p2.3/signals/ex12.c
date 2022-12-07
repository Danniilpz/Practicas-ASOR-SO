#include <signal.h>
#include <stdio.h>

struct sigaction act;
int cont_sigint=0;
int cont_sigtstp=0;

void handler(int signal){    
    if(signal==SIGINT){
        cont_sigint++;
    }
    else if(signal==SIGTSTP){
        cont_sigtstp++;
    }    
}

int main(){
    act.sa_handler=handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGTSTP,&act,NULL);
    while(cont_sigint+cont_sigtstp<10){}
    printf("SIGINT: %i\nSIGTSTP: %i\n",cont_sigint,cont_sigtstp);
    return 0;
}
