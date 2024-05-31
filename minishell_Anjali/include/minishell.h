/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:43 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/31 12:36:20 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<sys/param.h>
#include <fcntl.h>
#include <errno.h>

#define HISTORY_FILE ".minishell_history"
extern char **environ;

// Function prototypes
void display_prompt(void);
size_t	ft_strlen(const char *s);
void setup_signal_handlers(void);
void handle_sigint(int sig);
void handle_sigquit(int sig);
char **split_input(char *input);
void execute_command(char **args);
int ft_execvp(const char *args, char **argv);
//void execute_command(char **args);
int ft_newline(char **av);
void execute_command(char **args);
int	check_str(char *input);
void load_history();
void save_history();

int	ft_strcmp(char *str, char *in);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_minus_fd(char *s, int len, int fd);

int		my_strcmp(const char *s1, const char *s2);
int		shell_cd(char **args);
int		shell_echo(char **args);
int		shell_env(char **env);
int		shell_exit(char **args);
void		shell_export(char *arg);
int		shell_pwd(char **argv);
void	shell_unset(char **args);
int ft_newline(char **av);
void parser(char *input_command);
int	check_str(char *input);

int	print_error_msg_pipe(char *str);
int	print_error_msg_ampresent(char *str);
int	print_error_msg_closing_brace(char *str);
int	print_error_msg_closing_square(char *str);
int	print_error_msg_closing_curly(char *str);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
int	ft_strcmp(char *str, char *in);
#endif
