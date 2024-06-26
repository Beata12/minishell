/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 21:55:59 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int shell_cd(Token *args)
{
	if (!args[1].value)
	{
		fprintf(stderr, "cd: missing argument\n");
		return 1;
	}
	if (chdir(args[1].value) != 0)//changing diractory
	{
		perror("cd");
		return 1;
	}
	return (0);
}
