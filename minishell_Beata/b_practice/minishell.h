/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:08:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/28 16:26:55 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define HISTORY_FILE ".minishell_history"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_UNKNOWN
} TokenType;

typedef struct
{
	TokenType	type;
	char		*value;
} Token;

char	*my_strchr(const char *s, int c);
int		my_strcmp(const char *s1, const char *s2);
int		my_strlen(const char *s);
char	*my_strdup(char *src);
char	*my_strtok(char *str, const char *delimiters);

int		shell_cd(char **args);
int		shell_echo(char **args);
int		shell_env(char **env);
int		shell_exit(char **args);
void		shell_export(char *arg);
int		shell_pwd(char **argv);
void	shell_unset(char **args);
int ft_newline(char **av);

#endif