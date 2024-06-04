/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:15:07 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/04 21:27:11 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include "../Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include "parsing.h"

#define HISTORY_FILE ".minishell_history"
extern char **environ;

// Global variables

// Function prototypes
void execute_command(Token *tokens, int token_count);
void print_token_info(Token *tokens, int token_count);
void display_prompt(void);
size_t	ft_strlen(const char *s);
void setup_signal_handlers(void);
void handle_sigint(int sig);
void handle_sigquit(int sig);
//void execute_command(char **args);
int ft_newline(char **av);
int	check_str(char *input);
void load_history();
void save_history();

int	ft_strcmp(char *str, char *in);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_minus_fd(char *s, int len, int fd);

int		my_strcmp(const char *s1, const char *s2);
int		shell_cd(Token *args);
// int     shell_echo(Token tokens[], int token_count);
int shell_echo(Token *args);
// int		shell_echo(Token *args);
int		shell_env(void);
int     shell_exit(Token *args);
int	shell_export(Token *args);
int		shell_pwd(Token *argv);
void	shell_unset(Token *args);
int     shell_ls(Token tokens[], int token_count);
int     shell_touch(Token tokens[], int token_count);
int     shell_rm(Token tokens[], int token_count);
int     shell_rmdir(Token tokens[], int token_count);
int     shell_mkdir(Token tokens[], int token_count);
int     shell_clear(void);
int     ft_newline(char **av);
void    parser(char *input_command);
int     check_str(char *input);

int	    print_error_msg_pipe(char *str);
int 	print_error_msg_ampresent(char *str);
int 	print_error_msg_closing_brace(char *str);
int	    print_error_msg_closing_square(char *str);
int 	print_error_msg_closing_curly(char *str);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
int	    ft_strcmp(char *str, char *in);
void handle_redirection(Token *tokens, int token_count);
void handle_heredoc(Token *tokens, int token_count);
// void handle_redirection(char *input);

#endif
