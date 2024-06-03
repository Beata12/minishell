/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:01:18 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 10:08:01 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void redirect_input(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void redirect_output(const char *filename, int append) {
    int fd = open(filename, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void handle_heredoc(const char *delimiter) {
    char *line = NULL;
    size_t len = 0;
    FILE *tmp_file = tmpfile(); // Zmieniona nazwa zmiennej

    if (!tmp_file) {
        perror("tmpfile");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("> ");
        getline(&line, &len, stdin);
        if (strncmp(line, delimiter, strlen(delimiter)) == 0
			&& line[strlen(delimiter)] == '\n') {
            break;
        }
        fprintf(tmp_file, "%s", line);
    }

    fseek(tmp_file, 0, SEEK_SET);
    if (dup2(fileno(tmp_file), STDIN_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    free(line);
    fclose(tmp_file);
}

void handle_redirection(char *input)
{
    char *token;
    char *filename;
    int append = 0;

    while ((token = strpbrk(input, "<>"))) {
        if (*token == '<') {
            if (*(token + 1) == '<') { // handle heredoc
                *token = '\0';
                filename = strtok(token + 2, " ");
                handle_heredoc(filename);
            } else { // handle input redirection
                *token = '\0';
                filename = strtok(token + 1, " ");
                redirect_input(filename);
            }
        } else if (*token == '>') {
            if (*(token + 1) == '>') { // handle output append redirection
                append = 1;
                *token = '\0';
                filename = strtok(token + 2, " ");
            } else { // handle output redirection
                append = 0;
                *token = '\0';
                filename = strtok(token + 1, " ");
            }
            redirect_output(filename, append);
        }
        input = token + strlen(filename) + 1;
    }
}
