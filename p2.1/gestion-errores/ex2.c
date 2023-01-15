#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {

   if(setuid(0) == -1){
	   perror("Error %d: %s\n", errno, strerror(errno));
   }

   return 1;
}
