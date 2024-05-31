/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:48:22 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/31 12:27:45 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../include/parsing.h"

void	execute_command(Token *tokens, int token_count)
{
	char	*args[64];
	int		arg_count;
	int		i;
    int    pid_cd, pid_env, pid_echo, pid_pwd, pid_export, pid_unset;
	
	arg_count = 0;
	i = 0;
	while (i < token_count)
	{
		if (tokens[i].type == TOKEN_WORD)
			args[arg_count++] = tokens[i].value;
		i++;
	}
	args[arg_count] = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("fork() error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{

		if (ft_execvp(args[0], args) == 1)
		{
			perror("execvp() error");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}