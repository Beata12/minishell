#include "../header_files/shell_commands.h"

int shell_env(void)
{
    extern char **environ;
    for (char **env = environ; *env != 0; env++)
        printf("%s\n", *env);
    return 0;
}

int main() {
    shell_env();
    return 0;
}