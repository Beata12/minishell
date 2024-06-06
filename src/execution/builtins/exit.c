/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:42 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/06 15:23:50 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parsing.h"

int	shell_exit(Token *args)
{
	// Free memory allocated for each argument
	if (args != NULL)
	{
		for (int i = 0; args[i].value2 != NULL; i++)
		{
			free(args[i].value2);
		}
		// free(args);
	}
	exit(0);
}
