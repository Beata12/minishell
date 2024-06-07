/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:41:36 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/07 16:11:34 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# define HISTORY_FILE "./.minishell_history"
# define RE "\001\033[0m\002"
# define RED "\001\033[1;31m\002"
# define BLUE "\001\033[1;34m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define MAGENTA "\001\033[0;35m\002"
# define LIGHTGREEN "\001\033[1;32m\002"
# define CYAN "\001\033[0;36m\002"

# include "../Libft/libft.h"
# include "execution.h"
# include "parsing.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Beqa
// typedef struct s_list
// {
//     char *content;
//     struct s_list *next;
// } t_list;

// Global variables

// Signal handling
void	setup_signal_handlers(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

// Parsing
char	*parser(char *input_command);

// Prompt
void	display_prompt(char **env);

// Command execution
void	ft_execute(char **cmds, char **env);
void	ft_exec_built_in(char *cmd, char **env);
void	ft_execute_cmd(char *argv, char *envp[]);
char	**split_input(char *input);
// int		ft_execvp(const char *args, char **argv);
// void	ft_execute_command(Token *tokens, int token_count);

// History management
void	load_history(void);
void	save_history(void);

// Built-in shell commands
int		shell_cd(Token *args);
int		shell_echo(Token *args);
int		shell_env(void);
int		shell_exit(Token *args);
int		shell_export(Token *args);
int		shell_pwd(Token *argv);
void	shell_unset(Token *args);
int		shell_ls(Token tokens[], int token_count);
int		shell_touch(Token tokens[], int token_count);
int		shell_rm(Token tokens[], int token_count);
int		shell_rmdir(Token tokens[], int token_count);
int		shell_mkdir(Token tokens[], int token_count);
int		shell_clear(void);

// Redirection handling
void	handle_redirection(char *input);
void	handle_heredoc(const char *delimiter);

// Utility functions
int		check_str(char *input);
int		print_error_msg_pipe(char *str);
int		print_error_msg_ampresent(char *str);
int		print_error_msg_closing_brace(char *str);
int		print_error_msg_closing_square(char *str);
int		print_error_msg_closing_curly(char *str);
int		ft_newline(char **av);

// Libft function prototypes (if not included in libft.h)
int		my_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_minus_fd(char *s, int len, int fd);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *str, char *in);
int		ft_strcmp(char *str, char *in);

// Function prototypes
// void execute_command(char **args);

// void handle_redirection(char *input);

#endif
