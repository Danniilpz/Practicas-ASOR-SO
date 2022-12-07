#include <time.h>
int main() {
   time_t h=time(NULL);
   struct tm *t=localtime(&h);
   printf("%i\n",t->tm_year+1900);
}
