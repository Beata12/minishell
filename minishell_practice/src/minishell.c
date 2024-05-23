/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:33 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/23 17:37:00 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_executable(char *cmd) {
    char *path_env = getenv("PATH");
    if (!path_env) return NULL;

    char *path = strdup(path_env);
    if (!path) return NULL;

    char *dir = strtok(path, ":");
    while (dir) {
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0) {
            free(path);
            return strdup(full_path);
        }
        dir = strtok(NULL, ":");
    }
    free(path);
    return NULL;
}

void execute_command(char **argv, char **envp) {
    pid_t pid;
    int status;

    if (argv[0] == NULL) {
        return; // No command entered
    }

    if ((pid = fork()) == 0) { // Child process
        char *cmd_path;

        // Check if the command is an absolute or relative path
        if (strchr(argv[0], '/') != NULL) {
            cmd_path = argv[0];
        } else {
            cmd_path = find_executable(argv[0]);
            if (!cmd_path) {
                fprintf(stderr, "minishell: command not found: %s\n", argv[0]);
                exit(EXIT_FAILURE);
            }
        }

        if (execve(cmd_path, argv, envp) == -1) {
            perror("minishell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        // Parent process waits for the child to complete
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void parse_input(char *line, char **argv) {
    int i = 0;
    argv[i] = strtok(line, " ");
    while (argv[i] != NULL) {
        i++;
        argv[i] = strtok(NULL, " ");
    }
}

void display_prompt(char **envp) {
    char *input;
    char *argv[100];

    while (1) {
        // Display the prompt and read input
        input = readline("minishell> ");

        // If readline encounters EOF, it returns NULL
        if (!input) {
            //printf("\n");
            break;
        }

        // If the input is not empty, add it to the history
        if (*input) {
            add_history(input);
        }

        // For now, just print the input
        printf("You entered: %s\n", input);

        parse_input(input, argv);
        execute_command(argv, envp);

        // Free the allocated input
        free(input);
    }
}

int main(int argc, char **argv, char **envp) 
{
    (void)argc;
    (void)argv;
	display_prompt(envp);
    return 0;
}
