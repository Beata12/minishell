/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:43 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/29 14:32:34 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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
int g_exit_status;
extern char **environ;

// Function prototypes
void display_prompt(void);
void setup_signal_handlers(void);
void handle_sigint(int sig);
void handle_sigquit(int sig);
char **split_input(char *input);
void execute_command(char **args);
//void execute_command(char **args);
int ft_newline(char **av);
void execute_command(char **args);
void load_history();
void save_history();


int		my_strcmp(const char *s1, const char *s2);
int		shell_cd(char **args);
int		shell_echo(char **args);
int		shell_env(char **env);
int		shell_exit(char **args);
void		shell_export(char *arg);
int		shell_pwd(char **argv);
void	shell_unset(char **args);
int ft_newline(char **av);
#endif
