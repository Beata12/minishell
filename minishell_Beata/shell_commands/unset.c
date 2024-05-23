#include "../header_files/shell_commands.h"

int shell_unset(char **args)
{
    if (!args[1])
	{
        fprintf(stderr, "unset: missing argument\n");
        return 1;
    }
    if (unsetenv(args[1]) != 0)
	{
        perror("unset");
        return 1;
    }
    return 0;
}

