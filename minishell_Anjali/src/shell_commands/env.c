/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:40 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/31 12:33:43 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int shell_env(char **env)
{
    extern char **environ;
    for (env = environ; *env != 0; env++)
        printf("%s\n", *env);
    return (0);
}

// int main()
// {
//     shell_env();
//     return (0);
// }