#include <unistd.h>
#include <stdio.h>

int main() {
   if(setuid(2)==0){
	printf("%d",getuid());
   }
   else perror("ERROR");
   return 0;
}
