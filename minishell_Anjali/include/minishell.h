/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:43 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/28 18:16:12 by aneekhra         ###   ########.fr       */
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

// Function prototypes
void display_prompt(char **envp);
void setup_signal_handlers(void);
void handle_sigint(int sig);
void handle_sigquit(int sig);
char **split_input(char *input);
void execute_command(char **args);
//void execute_command(char **args);
void load_history();
void save_history();

#endif
