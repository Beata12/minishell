#include "../header_files/shell_commands.h"

int shell_pwd(void)
{
    char *cwd;
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
	else
        perror("pwd");
    return 0;
}