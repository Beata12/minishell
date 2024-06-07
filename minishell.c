/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:08:59 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/07 12:46:11 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/execution.h"
#include "include/minishell.h"
#include "include/parsing.h"

char	**split_input(char *input)
{
	char	*arg;
	int		position;
	char	**args;

	args = malloc(64 * sizeof(char *));
	// Allocate space for 64 arguments
	position = 0;
	arg = strtok(input, " "); // Split input by spaces
	while (arg != NULL)
	{
		args[position++] = arg;
		arg = strtok(NULL, " ");
	}
	args[position] = NULL; // Null-terminate the array of arguments
	return (args);
}

void	display_prompt(char **env)
{
	char	*input;
	char	**cmds;

	(void)env;
	load_history();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (!*input)
		{ // parser(input);
			continue ;
		}
		cmds = ft_split(input, '|'); // parse the input
		ft_execute(cmds, env);
		free(input);
	}
	save_history();
}

int	main(int argc, char **argv, char **env)
{
	int	g_exit_status;

	if (!argc && !argv)
		return (0);
	if (argc != 1)
	{
		exit(write(1, RED "	No arguments accepted!	\n" RE, 32));
	}
	g_exit_status = 0;
	ft_printf(BLUE " 	WELCOME TO MINISHELL!		\n" RE);
	setup_signal_handlers();
	display_prompt(env);
	return (g_exit_status);
}

// // Function to find the full path of an executable
// char *find_executable(char *command)
// {
// 	char *path = getenv("PATH");
// 	char *token;
// 	char full_path[1024];

// 	// If the command is an absolute or relative path,  return it directly
// 	if (strchr(command, '/') != NULL)
// 		return (command);

// 	// Search for the command in the PATH directories
// 	token = strtok(path, ":");
// 	while (token != NULL)
// 	{
// 		full_path[0] = '\0';
// 		strcat(full_path, token);
// 		strcat(full_path, "/");
// 		strcat(full_path, command);

// 		if (access(full_path, X_OK) == 0)
// 		{
// 			char *executable = malloc(strlen(full_path) + 1);
// 			strcpy(executable, full_path);
// 			return (executable);
// 		}
// 		token = strtok(NULL, ":");
// 	}
// 	return (NULL);
// }
// int ft_newline(char **av)
// {
// 	(void)av;
// 	printf("\n");
// 	return (0);
// }
// int ft_execvp(const char *args, char **argv)
// {
// 	if (my_strcmp(args, "e") == 0)
// 		return ;
// 	// else if (my_strcmp(args, "env") == 0)
// 	// 	return (shell_env(argv));
// 	// else if (my_strcmp(args, "cd") == 0)
// 	// 	return (shell_cd(argv));
// 	// else if (my_strcmp(args, "exit") == 0)
// 	// 	return (0);
// 	// else if (my_strcmp(args, "pwd") == 0)
// 	// 	return (shell_pwd(argv));
// 	// else if (my_strcmp(args, "unset") == 0)
// 	// 	{shell_unset(argv);
// 	// 	return (0);}
// 	// else if (my_strcmp(args, "\n") == 0)
// 	// 	return (ft_newline(argv));
// 	else
// 		printf("command not found\n");
// 	return (0);
// }

// // Function to execute a command
// void execute_command(char **args)
// {
// 	char *command = args[0];
// 	char *executable = find_executable(command);

// 	if (executable == NULL)
// 	{
// 		printf("minishell: command not found: %s\n", command);
// 		return ;
// 	}

// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
// 		// Child process
// 		if (ft_execvp(args[0], args) == -1)
// 		{
// 			perror("minishell");
// 		}
// 		exit(EXIT_FAILURE);
// 	} else if (pid < 0)
// 	{
// 		// Error forking
// 		perror("minishell");
// 	}
// 	else
// 	{
// 		// Parent process
// 		int status;
// 		waitpid(pid, &status, 0);
// 	}
// p0\ 	// Free the allocated memory for the executable path if it was duplicated]
// 	free(executable);
// }

// void error_str(void)
// {
// 	g_exit_status = 258;
// }

// char	*find_path(char *cmd, char *path)
// {
// 	char	*c;
// 	char	*tmp;
// 	char	**paths;
// 	int		i;
// 	int		fd;

// 	i = 0;
// 	paths = ft_split(path, ':');
// 	while (paths[i] != NULL)
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		c = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		fd = open(c, O_RDONLY);
// 		if (fd != -1)
// 		{
// 			close(fd);
// 			return (c);
// 		}
// 		free(c);
// 		i++;
// 	}
// 	return (NULL);
// }

// void ft_exe(char *cmd, char **env);

// void ft_execute(char **cmds, char **env)
// {
// 	int fd[2];
// 	pid_t pid;
// 	int i = 0;
// 	int pipes = 0 ;
// 	while(cmds[i] != NULL)
// 	{
// 		i++;
// 		pipes++;
// 	}
// 	i = 0;
// 	while (i < pipes)
// 	{
// 		pipe(fd);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (i != 0)
// 			{
// 				dup2(fd[0], 0);
// 				close(fd[0]);
// 			}
// 			if (cmds[i + 1] != NULL)
// 				dup2(fd[1], 1);
// 			//Beqa
// 			//heardoc
// 			// open_input_files(args->input_files);
// 			// open_output_files(args->output_files);
// 			// close(fd[1]);
// 			ft_exe(cmds[i], env);
// 			exit(0);
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 			close (fd[0]);
// 			close(fd[1]);
// 			fd[0] = fd[0];
// 		}
// 		i++;
// 	}
// }

// void execute(char *input, char **env);
// void ft_exe(char *cmd, char **env)
// {
// 	if (ft_strncmp(cmd, "cd", 2) == 0)
// 		printf("cd\n");
// 	else if (ft_strncmp(cmd, "echo", 4) == 0)
// 		printf("echo\n");
// 	else if (ft_strncmp(cmd, "env", 3) == 0)
// 		printf("env\n");
// 	else if (ft_strncmp(cmd, "exit", 4)	== 0)
// 		printf("exit\n");
// 	else if (ft_strncmp(cmd, "export", 6) == 0)
// 		printf("export\n");
// 	else if (ft_strncmp(cmd, "pwd", 3)	== 0)
// 		printf("pwd\n");
// 	else if (ft_strncmp(cmd, "unset", 5) == 0)
// 		printf("unset\n");
// 	else
// 		execute(cmd, env);
// }

// void execute(char *input, char **env)
// {
// 	char **cmds = ft_split(input, ' ');
// 	int i = 0;
// 	while(ft_strncmp(env[i], "PATH=", 5) != 0)
// 		i++;
// 	char *tmp = env[i];
// 	if (ft_strchr(cmds[0], '/') != NULL)
// 	{
// 		execve(cmds[0], cmds, env);
// 	}
// 	char *path = find_path(cmds[0], tmp);
// 	if (path == NULL)
// 	{
// 		printf("Command not found\n");
// 		exit(0);
// 	}
// 	execve(path, cmds, env);
// 	free(path);
// 	exit(0);
// }