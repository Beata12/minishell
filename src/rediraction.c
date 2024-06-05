/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:01:18 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/04 21:29:56 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

void    handle_heredoc(Token *tokens,int token_count)
{
    char *line = NULL;
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("> ");
        line = get_next_line(STDIN_FILENO);
        if (line == NULL) {
            perror("get_next_line");
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            exit(EXIT_FAILURE);
        }
        if (strncmp(line, tokens[token_count].value, strlen(tokens[token_count].value)) == 0 && line[strlen(tokens[token_count].value)] == '\n') {
            free(line);
            break;
        }
        write(pipe_fd[1], line, strlen(line));
        free(line);
    }
    close(pipe_fd[1]); // Close the write end of the pipe

    if (dup2(pipe_fd[0], STDIN_FILENO) == -1) {
        perror("dup2");
        close(pipe_fd[0]);
        exit(EXIT_FAILURE);
    }
    close(pipe_fd[0]); // Close the read end of the pipe after dup2
}

int redirect_input(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int redirect_output(const char *filename, int append) {
    int fd;
    if (append) {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (fd == -1) {
        perror("open");
        return -1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return -1;
    }

    close(fd);
    return 0; // Return 0 on success
}

void handle_redirection(Token *tokens, int token_count) {
    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type == T_RED_TO) {
            int fd = open(tokens[i+1].value, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd < 0) {
                perror("Error opening file");
                exit(1);
            }
            
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (tokens[i].type == T_DGREAT) {
            int fd = open(tokens[i+1].value, O_WRONLY | O_CREAT | O_APPEND, 0666);
            if (fd < 0) {
                perror("Error opening file");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (tokens[i].type == T_RED_FROM) {
            int fd = open(tokens[i+1].value, O_RDONLY);
            if (fd < 0) {
                perror("Error opening file");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
    }
}
