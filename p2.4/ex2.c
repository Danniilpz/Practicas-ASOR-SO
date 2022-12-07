#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char * argv[]){
    int p_h[2];
    int h_p[2];
    pipe(p_h);
    pipe(h_p);
    pid_t pid=fork();
    if(pid==0){
        close(p_h[1]);
        close(h_p[0]);
        char buf[50];
        int n=0;
        do{
            read(p_h[0],buf,50);
            sleep(1);
            write(h_p[1],"l",1);
            n++;
        }while(n<9);
        write(h_p[1],"q",1);
        close(p_h[0]);
        close(h_p[1]);
    }
    else{
        close(p_h[0]);
        close(h_p[1]);
        char buf[50];
        do{
            read(0,buf,50);
            write(p_h[1],buf,50);   
            read(h_p[0],buf,50);
        }while(strcmp(buf, "q") != 0);
        close(p_h[1]);
        close(h_p[0]);
    }
    return 0;
}