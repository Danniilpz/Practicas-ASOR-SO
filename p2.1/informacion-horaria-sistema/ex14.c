#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
   if( (time_t t=time(NULL)) == -1) handle_error("Error in time()");
   if( (struct tm *info=localtime(&t)) == -1) handle_error("Error in localtime()");

   printf("Current year: %i\n",info->tm_year + 1900);
   
   return 0;
}
