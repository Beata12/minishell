/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:18:58 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/26 15:45:44 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
extern char **environ;

#define HISTORY_FILE ".minishell_history"

// Function to load command history
void load_history() {
    read_history(HISTORY_FILE);
}

// Function to save command history
void save_history() {
    write_history(HISTORY_FILE);
}

// Function to split input into arguments
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
    size_t len;  // Use size_t to match the type of sizeof

    // If the command is an absolute or relative path, return it directly
    if (strchr(command, '/') != NULL) {
        return command;
    }

    // Search for the command in the PATH directories
    token = strtok(path, ":");
    while (token != NULL) {
        len = strlen(token) + strlen(command) + 2; // +2 for '/' and null terminator
        if (len >= sizeof(full_path)) {
            token = strtok(NULL, ":");
            continue;
        }

        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, command);

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

void display_prompt(char **envp) 
{
    (void)envp;

    char *cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	printf("@minishell:%s$ ", cwd);
	free(cwd);



    // char *input;

    // load_history();

    // while (1) {
    //     // Display the prompt and read input
    //     input = readline("minishell> ");

    //     // If readline encounters EOF, it returns NULL
    //     if (!input) {
    //         printf("\n");
    //         break;
    //     }

    //     // If the input is not empty, add it to the history
    //     if (*input) {
    //         add_history(input);
    //     }

    //     // Split the input into command and arguments
    //     char **args = split_input(input);

    //     // Execute the command
    //     if (args[0] != NULL) {
    //         execute_command(args);
    //     }

    //     // Free the allocated input and arguments
    //     free(input);
    //     free(args);
    //}
   // save_history();
}
int main(int ac, char **av, char **envp) {
    char	*command;
	int		token_count;
	int		i;

	i = 0;
    (void)ac;
    (void)av;
    display_prompt(envp);

		command = readline(NULL);
		if (command == NULL)
			break ;
		if (strlen(command) > 0)
		{
			add_history(command);
			Token	*tokens = tokenize(command, &token_count);
			if (parse_tokens(tokens, token_count))
			{
				// if (strcmp(tokens[0].value, "touch") == 0)
					// shell_echo(&tokens[1].value);
					execute_command(tokens, token_count);
			}
			while (i < token_count)
			{
				free(tokens[i].value);
				i++;
			}
			free(tokens);
		}
		free(command);
	}
	save_history();

    return 0;
}
