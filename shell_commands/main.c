#include "../header_files/shell_commands.h"

void execute_command(char *cmd) {
    char *args[1024];
    int i = 0;

    args[i] = strtok(cmd, " ");
    while (args[i])
        args[++i] = strtok(NULL, " ");
    if (strcmp(args[0], "echo") == 0)
        shell_echo(args);
    else if (strcmp(args[0], "cd") == 0)
        shell_cd(args);
    else if (strcmp(args[0], "pwd") == 0)
        shell_pwd();
    else if (strcmp(args[0], "export") == 0)
        shell_export(args);
    else if (strcmp(args[0], "unset") == 0)
        shell_unset(args);
    else if (strcmp(args[0], "env") == 0)
        shell_env();
    else if (strcmp(args[0], "exit") == 0)
        shell_exit();
    else
	{
        pid_t pid = fork();
        if (pid == 0) 
		{
            execvp(args[0], args);
            perror("minishell");
            exit(EXIT_FAILURE);
        } 
		else
            waitpid(pid, NULL, 0);
    }
}
