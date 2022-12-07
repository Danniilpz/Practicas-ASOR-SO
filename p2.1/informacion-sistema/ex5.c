#include <sys/utsname.h>

int main() {
    struct utsname info;
    uname(&info);
    printf("sysname: %s\n",info.sysname);
    printf("nodename: %s\n",info.nodename);
    printf("release: %s\n",info.release);
    printf("version: %s\n",info.version);
    printf("machine: %s\n",info.machine);
}
