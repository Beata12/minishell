/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:56 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/24 10:48:25 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/shell_commands.h"

int shell_pwd(void)
{
    char *cwd;
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
	else
        perror("pwd");
    return (0);
}