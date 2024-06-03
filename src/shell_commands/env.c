/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:40 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 21:46:05 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int shell_env(void)
{
    extern char **environ;
    if (environ == NULL)
    {
        fprintf(stderr, "Error: environ is NULL\n");
        return -1;
    }

    for (char **env = environ; *env != NULL; env++)
    {
        if (*env == NULL)
        {
            fprintf(stderr, "Warning: Null environment variable encountered\n");
            continue;
        }
        printf("%s\n", *env);
    }
    return 0;
}
