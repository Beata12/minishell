/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:56 by bmarek            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/31 12:22:40 by bmarek           ###   ########.fr       */
=======
/*   Updated: 2024/05/31 12:27:27 by aneekhra         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int shell_pwd(char **argv)
{
	if (*argv == NULL)
		return (0);
	char *cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}