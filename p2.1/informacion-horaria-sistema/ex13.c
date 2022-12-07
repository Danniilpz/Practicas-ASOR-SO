#include <sys/time.h>
#include <unistd.h>
int main() {
   struct timeval tv;
   gettimeofday(&tv,NULL);
   long micro1=tv.tv_usec;
   for(int i=0;i<1000000;i++){
   }
   gettimeofday(&tv,NULL);
   long micro2=tv.tv_usec;
   printf("%li\n",micro2-micro1);
}
