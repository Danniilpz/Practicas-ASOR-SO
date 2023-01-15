#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

int cont_sigint=0;
int cont_sigtstp=0;

void handler(int signal){    
    if(signal == SIGINT) cont_sigint++;
    else if(signal == SIGTSTP) cont_sigtstp++;    
}

int main(){
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags = 0;

    if(sigemptyset(&act.sa_mask) == -1) handle_error("Error in sigemptyset()");
    
    if(sigaction(SIGINT, &act, NULL) == -1) handle_error("Error en sigaction()");
    if(sigaction(SIGTSTP, &act, NULL) == -1) handle_error("Error en sigaction()");

    while((cont_sigint + cont_sigtstp) < 10){}

    printf("SIGINT: %i\nSIGTSTP: %i\n", cont_sigint, cont_sigtstp);

    return 0;
}
