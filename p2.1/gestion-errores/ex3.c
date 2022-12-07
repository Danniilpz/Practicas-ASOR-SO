#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
   for(int i=0;i<255;i++){
	char *pointer=strerror(i);
	printf("%s\n",pointer);
   }
   return 0;
}
