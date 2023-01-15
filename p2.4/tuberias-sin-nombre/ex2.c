#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define throw_error(msg) \
          do { fprintf(stderr,"%s\n",msg); exit(EXIT_FAILURE); } while (0)

int main(){
    int p_h[2];
    int h_p[2];

    if(pipe(p_h) == -1) handle_error("Error in pipe()");
    if(pipe(h_p) == -1) handle_error("Error in pipe()");

    char buf[50];
    pid_t pid = fork();
    switch(pid){
        case -1:
            handle_error("Error in fork()");
            break;
        case 0: //Child
            close(p_h[1]);
            close(h_p[0]);

            int n = 0;
            do{
                read(p_h[0], buf, 50);
                sleep(1);
                write(h_p[1], "l", 1);
                n++;
            }while(n < 9);

            write(h_p[1], "q", 1);
            
            close(p_h[0]);
            close(h_p[1]);
            break;
        case 1: //Parent
            close(p_h[0]);
            close(h_p[1]);

            do{
                read(0, buf, 50);
                write(p_h[1], buf, 50);   
                read(h_p[0], buf, 50);
            }while(strcmp(buf, "q") != 0);

            close(p_h[1]);
            close(h_p[0]);
            break;
    }

    return 0;
}