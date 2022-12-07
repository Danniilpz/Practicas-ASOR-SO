#include <unistd.h>
#include <stdio.h>

int main() {
    printf("%d\n",sysconf(_SC_ARG_MAX));
    printf("%d\n",sysconf(_SC_CHILD_MAX));
    printf("%d\n",sysconf(_SC_OPEN_MAX));
}
