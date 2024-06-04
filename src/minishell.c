/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:08:59 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/04 20:38:49 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

int g_exit_status;
// Signal handlers
void handle_sigint(int sig)
{
	g_exit_status = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();

	if (sig == SIGTSTP || sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handle_sigquit(int sig)
{
	(void)sig;
	// Do nothing on Ctrl-
}

void setup_signal_handlers(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void load_history(void)
{
	read_history(HISTORY_FILE);
}

void save_history(void)
{
	write_history(HISTORY_FILE);
}

void error_str(void)
{
	g_exit_status = 258;
}

void display_prompt(void)
{
	char *input;

	load_history();
	
	 while (1) {
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		if (check_str(input) != 0)
			error_str();
		else
			parser(input);
		free(input);
	}
	save_history();
}

int main(int argc, char **argv)
{
	if (!argc && !argv)
		return (0);
	g_exit_status = 0;
	ft_printf("Welcome to minishell!\n");
	setup_signal_handlers();
	display_prompt();
	return g_exit_status;
}
