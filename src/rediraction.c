/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:01:18 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/05 19:36:13 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_heredoc(const char *delimiter)
{
	char	*line = NULL;
	int	len = 0;
	FILE	*tmp_file = tmpfile();

	if (!tmp_file) {
		perror("tmpfile");
		exit(EXIT_FAILURE);
	}
    int fd = open(delimiter, O_RDONLY);
	while (1)
	{
		printf("> ");
		get_next_line(fd);
		if (strncmp(line, delimiter, strlen(delimiter)) == 0
			&& line[strlen(delimiter)] == '\n')
		{
			break;
		}
		fprintf(tmp_file, "%s", line);
	}
	fseek(tmp_file, 0, SEEK_SET);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	free(line);
	//fclose(tmp_file);
}


int redirect_input(const char *filename)
{       
    int fd = open(filename, O_RDONLY);
    
    if (fd == -1)
    {
        perror("open");
        return -1; // Zwracamy -1 w przypadku błędu
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return -1; // Zwracamy -1 w przypadku błędu
    }
    close(fd);
    return 0; // Zwracamy 0 w przypadku sukcesu
}

int redirect_output(const char *filename, int append)
{
    int fd = open(filename, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
    
    if (fd == -1)
    {
        perror("open");
        return -1; // Zwracamy -1 w przypadku błędu
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return -1; // Zwracamy -1 w przypadku błędu
    }
    close(fd);
    return 0; // Zwracamy 0 w przypadku sukcesu
}


void handle_redirection(char *input)
{
    char *token;
    char *filename;
    int append = 0;

    while ((token = strpbrk(input, "<>")))
    {
        if (*token == '<')
        {
            if (*(token + 1) == '<')
            { // handle heredoc
                *token = '\0';
                filename = strtok(token + 2, " ");
                handle_heredoc(filename);
            }
            else
            { // handle input redirection
                *token = '\0';
                filename = strtok(token + 1, " ");
                if (redirect_input(filename) == -1) {
                    perror("redirect_input");
                    return; // Kontynuujemy działanie pomimo błędu
                }
            }
        }
        else if (*token == '>')
        {
            if (*(token + 1) == '>')
            { // handle output append redirection
                append = 1;
                *token = '\0';
                filename = strtok(token + 2, " ");
            }
            else
            { // handle output redirection
                append = 0;
                *token = '\0';
                filename = strtok(token + 1, " ");
            }
            if (redirect_output(filename, append) == -1) {
                perror("redirect_output");
                return; // Kontynuujemy działanie pomimo błędu
            }
        }
        input = token + strlen(filename) + 1;
    }
}

// void	handle_redirection(char *input)
// {
// 	char	*token;
// 	char	*filename;
// 	int		append = 0;

// 	while ((token = strpbrk(input, "<>")))
// 	{
// 		if (*token == '<')
// 		{
// 			if (*(token + 1) == '<')
// 			{// handle heredoc
// 				*token = '\0';
// 				filename = strtok(token + 2, " ");
// 				handle_heredoc(filename);
// 			}
// 			else
// 			{// handle input redirection
// 				*token = '\0';
// 				filename = strtok(token + 1, " ");
// 				redirect_input(filename);
// 			}
// 		}
// 		else if (*token == '>')
// 		{
// 			if (*(token + 1) == '>')
// 			{// handle output append redirection
// 				append = 1;
// 				*token = '\0';
// 				filename = strtok(token + 2, " ");
// 			}
// 			else
// 			{// handle output redirection
// 				append = 0;
// 				*token = '\0';
// 				filename = strtok(token + 1, " ");
// 			}
// 			redirect_output(filename, append);
// 		}
// 		input = token + strlen(filename) + 1;
// 	}
// }