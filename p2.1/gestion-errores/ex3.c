#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {

   for(int i = 0; i < 255; i++){
      printf("Error %d: %s\n", i, strerror(i));
   }

   return 1;
}
