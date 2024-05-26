/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:40 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/26 12:21:31 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/shell_commands.h"

int shell_env(void)
{
    extern char **environ;
    for (char **env = environ; *env != 0; env++)
        printf("%s\n", *env);
    return (0);
}

int main()
{
    shell_env();
    return (0);
}