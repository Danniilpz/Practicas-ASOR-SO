#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
          do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main() {
    
    if(geteuid() == -1 || getuid == -1 || getpwuid(getuid()) == -1) handle_error("Error");

    printf("Real UID: %li\n",getuid());
    printf("Effective UID: %li\n",geteuid());

    //if UID and EUID are different, setuid bit must be 1

    struct passwd *info=getpwuid(getuid());

    printf("Nombre de usuario: %s\n",info->pw_name);
    printf("Directorio home: %s\n",info->pw_dir);
    printf("Descripción del usuario: %s\n",info->pw_gecos);

    return 1;
}
