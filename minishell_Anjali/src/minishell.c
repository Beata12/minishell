/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:33 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/26 15:09:01 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define HISTORY_FILE ".minishell_history"

// Signal handlers
void handle_sigint(int sig) {
    (void)sig;
    // Use rl_replace_line and rl_redisplay to properly handle the prompt display
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void handle_sigquit(int sig) {
    (void)sig;
    // Do nothing on Ctrl-
}

void setup_signal_handlers() {
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void load_history() {
    read_history(HISTORY_FILE);
}

void save_history() {
    write_history(HISTORY_FILE);
}

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

    load_history();

    while (1) {
        input = readline("minishell> ");
        if (!input) {
            // Handle ctrl-D (EOF)
            printf("\n");
            break;
        }

        if (*input) {
            add_history(input);
        }

        parse_input(input, argv);
        execute_command(argv, envp);

        free(input);
    }

    save_history();
}

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;

    // Setup signal handlers
    setup_signal_handlers();

    display_prompt(envp);
    return 0;
}