/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:07:36 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/31 12:26:47 by aneekhra         ###   ########.fr       */
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