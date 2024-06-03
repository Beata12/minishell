/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:33 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/03 13:48:14 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_exit_status;
// Signal handlers
void handle_sigint(int sig)
{
	g_exit_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();

	if (sig == SIGTSTP || sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handle_sigquit(int sig)
{
	(void)sig;
	// Do nothing on Ctrl-
}

void setup_signal_handlers(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void load_history(void)
{
	read_history(HISTORY_FILE);
}

void save_history(void)
{
	write_history(HISTORY_FILE);
}

char **split_input(char *input)
{
	char **args = malloc(64 * sizeof(char*)); // Allocate space for 64 arguments
	char *arg;
	int position = 0;

	arg = strtok(input, " "); // Split input by spaces
	while (arg != NULL)
	{
		args[position++] = arg;
		arg = strtok(NULL, " ");
	}
	args[position] = NULL; // Null-terminate the array of arguments
	return args;
}

// Function to find the full path of an executable
char *find_executable(char *command)
{
	char *path = getenv("PATH");
	char *token;
	char full_path[1024];

	// If the command is an absolute or relative path, return it directly
	if (strchr(command, '/') != NULL)
		return command;

	// Search for the command in the PATH directories
	token = strtok(path, ":");
	while (token != NULL)
	{
		full_path[0] = '\0';
		strcat(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			char *executable = malloc(strlen(full_path) + 1);
			strcpy(executable, full_path);
			return executable;
		}
		token = strtok(NULL, ":");
	}
	return NULL;
}
int ft_newline(char **av)
{
	(void)av;
	printf("\n");
	return (0);
}
int ft_execvp(const char *args, char **argv)
{
	if (my_strcmp(args, "echo") == 0)
		return (shell_echo(argv));
	else if (my_strcmp(args, "env") == 0)
		return (shell_env(argv));
	else if (my_strcmp(args, "cd") == 0)
		return (shell_cd(argv));
	else if (my_strcmp(args, "exit") == 0)
		return (shell_exit(argv));
	else if (my_strcmp(args, "pwd") == 0)
		return (shell_pwd(argv));
	else if (my_strcmp(args, "unset") == 0)
		{shell_unset(argv);
		return (0);}
	else if (my_strcmp(args, "\n") == 0)
		return ft_newline(argv);
	else
		printf("command not found\n");
	return (0);
}

// Function to execute a command
void execute_command(char **args)
{
	char *command = args[0];
	char *executable = find_executable(command);

	if (executable == NULL)
	{
		printf("minishell: command not found: %s\n", command);
		return;
	}

	pid_t pid = fork();
	if (pid == 0)
	{
		// Child process
		if (ft_execvp(args[0], args) == -1)
		{
			perror("minishell");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
	{
		// Error forking
		perror("minishell");
	}
	else
	{
		// Parent process
		int status;
		waitpid(pid, &status, 0);
	}
	// Free the allocated memory for the executable path if it was duplicated
	free(executable);
}

void error_str(void)
{
	g_exit_status = 258;
}

volatile sig_atomic_t sigint_received = 0;

// Signal handler function for SIGINT (Ctrl+C)
void sigint_handler(int signum) {
	sigint_received = 1;
}

void display_prompt(void)
{
	char *input;

	load_history();

	// Register SIGINT handler
	// signal(SIGINT, sigint_handler);
	
	 while (1) {
	// while (!sigint_received)
	// {
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		if (check_str(input) != 0)
			error_str();
		else
			// handle_redirection(input);
			parser(input);
		free(input);
	}
	save_history();
}

int main(int argc, char **argv)
{
	if (!argc && !argv)
		return (0);
	g_exit_status = 0;
	setup_signal_handlers();
	display_prompt();
	return g_exit_status;
}
