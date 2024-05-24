/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:08:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/24 12:52:54 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
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

//shell_commands
int		shell_cd(char **args);
int		shell_echo(char **args);
int		shell_env(void);
int		shell_exit(void);
int		shell_export(char *arg);
int		shell_pwd(void);
int		shell_unset(char **args);

#endif