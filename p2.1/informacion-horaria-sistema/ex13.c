#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
   struct timeval tv;

   if(gettimeofday(&tv,NULL) == -1) handle_error("Error in gettimeofday()");
   long start=tv.tv_usec;

   for(int i=0;i<1000000;i++){
   }

   if(gettimeofday(&tv,NULL) == -1) handle_error("Error in gettimeofday()");
   long end=tv.tv_usec;

   printf("Total time in ms: %li\n",start-end);

   return 0;
}
