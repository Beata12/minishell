/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:08:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/23 08:39:02 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_files/minishell.h"

void	display_prompt(void)
{
	char	*cwd = getcwd(NULL, 0);
	char	*username = getlogin();

	if (cwd == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	if (username == NULL)
	{
		perror("getlogin() error");
		free(cwd);
		exit(EXIT_FAILURE);
	}
	printf("%s@minishell:%s$ ", username, cwd);
	free(cwd);
}

void	execute_command(char *command)
{
	char	**args = NULL;
	char	*token = strtok(command, " ");
	int		i;
	pid_t	pid = fork();

	i = 0;
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	if (pid < 0)
	{
		perror("fork() error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) < 0)
		{
			perror("execvp() error");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
	free (args);
}

int	main(void)
{
	char	*command;

	while (1)
	{
		display_prompt();
		command = readline(NULL);
		if (command == NULL)
			break ;
		if (strlen(command) > 0)
		{
			add_history(command);
			execute_command(command);
		}
		free(command);
	}
	return (0);
}
