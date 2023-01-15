#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
    time_t t;
    struct tm *info;
    if( (t = time(NULL)) == -1) handle_error("Error in time()");
    if( (info = localtime(&t)) == -1) handle_error("Error in localtime()");

    printf("Current year: %i\n",info->tm_year + 1900);
   
    char buf[100];
    strftime(buf, 100, "%A, %H:%M", info);
    printf("Current date: %s\n", buf);

    return 0;
}
