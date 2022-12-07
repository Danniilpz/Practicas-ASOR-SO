#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
   if(setuid(2)==0){
	printf("%d",getuid());
   }
   else {
	printf("%d",errno);
	perror("Error");
	
   }
   return 0;
}

