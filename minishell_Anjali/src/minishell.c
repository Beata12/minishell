/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:33 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/28 18:14:49 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define HISTORY_FILE ".minishell_history"
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

void handle_sigquit(int sig) {
    (void)sig;
    // Do nothing on Ctrl-
}

void setup_signal_handlers(void) 
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void load_history() {
    read_history(HISTORY_FILE);
}

void save_history() {
    write_history(HISTORY_FILE);
}

char **split_input(char *input) {
    char **args = malloc(64 * sizeof(char*)); // Allocate space for 64 arguments
    char *arg;
    int position = 0;

    arg = strtok(input, " "); // Split input by spaces
    while (arg != NULL) {
        args[position++] = arg;
        arg = strtok(NULL, " ");
    }
    args[position] = NULL; // Null-terminate the array of arguments
    return args;
}

// Function to find the full path of an executable
char *find_executable(char *command) {
    char *path = getenv("PATH");
    char *token;
    char full_path[1024];

    // If the command is an absolute or relative path, return it directly
    if (strchr(command, '/') != NULL) {
        return command;
    }

    // Search for the command in the PATH directories
    token = strtok(path, ":");
    while (token != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(full_path, X_OK) == 0) {
            return strdup(full_path); // Return a copy of the full path
        }
        token = strtok(NULL, ":");
    }
    return NULL;
}

// Function to execute a command
void execute_command(char **args) {
    char *command = args[0];
    char *executable = find_executable(command);

    if (executable == NULL) {
        printf("minishell: command not found: %s\n", command);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execve(executable, args, environ) == -1) {
            perror("minishell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("minishell");
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }

    // Free the allocated memory for the executable path if it was duplicated
    if (executable != command) {
        free(executable);
    }
}

void	error_str(void)
{
	g_exit_status = 258;
}

void display_prompt(char **envp) {
    char *input;
    char **argv;

    load_history();
    *argv = NULL;
    while (1) {
        input = readline("minishell> ");
        add_history(input);
        if (!input)
        {
            printf("\n");
            break;
        }
        argv = split_input(input);
        if(argv[0] != NULL)
            execute_command(argv);
        free(input);
        free(argv);
    }
    save_history();
}

int main(int argc, char **argv, char **envp)
{
    g_exit_status = 0;
    setup_signal_handlers();
    if(!argc && !argv)
        return (0);
    display_prompt(envp);
    return (g_exit_status);
}