/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:38 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/31 12:35:30 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int shell_echo(char **args)
{
    int i = 1;
    int newline = 1;
    if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
        newline = 0;
        i++;
    }
    while (args[i])
	{
        printf("%s", args[i]);
        if (args[++i])
            printf(" ");
    }
    if (newline)
        printf("\n");
    return (0);
}

// int main(int argc, char *argv[])
// {
//     if (argc > 1)
//         shell_echo(&argv[1]);
//     else
//         printf("Usage: %s [options] [text]\n", argv[0]);
//     return (0);
// }