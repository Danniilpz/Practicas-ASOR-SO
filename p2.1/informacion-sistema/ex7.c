#include <unistd.h>

int main(){
   printf("_PC_LINK_MAX: %li\n",pathconf("ejer.c",_PC_LINK_MAX));
   printf("_PC_PATH_MAX: %li\n",pathconf("ejer.c",_PC_PATH_MAX));
   printf("_PC_NAME_MAX: %li\n",pathconf("ejer.c",_PC_NAME_MAX));
}
