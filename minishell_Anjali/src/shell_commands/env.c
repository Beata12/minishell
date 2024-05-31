/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:40 by bmarek            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/31 12:21:44 by bmarek           ###   ########.fr       */
=======
/*   Updated: 2024/05/31 12:27:13 by aneekhra         ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
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