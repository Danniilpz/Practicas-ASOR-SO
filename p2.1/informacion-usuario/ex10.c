#include <pwd.h>
#include <sys/types.h>

int main() {
    printf("EUID: %li\n",geteuid());
    printf("EGID: %li\n",getegid());
    struct passwd *info=getpwuid(getuid());
    printf("Nombre de usuario: %s\n",info->pw_name);
    printf("Directorio home: %s\n",info->pw_dir);
    printf("Descripción del usuario: %s\n",info->pw_gecos);
}
