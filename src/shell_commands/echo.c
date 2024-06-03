/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:38 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 22:15:54 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int shell_echo(Token *args)
// {
//     int i = 1; // Start after the "echo" command itself
//     int newline = 1;

//     // Check for the -n flag
//     if (args[i].value && ft_strcmp(args[i].value, "-n") == 0)
//     {
//         newline = 0;
//         i++;
//     }

//     // Print the arguments
//     while (args[i].value[0] != '\0')
//     {
//         printf("%s", args[i].value);
//         if (args[i + 1].value[0] != '\0')
//             printf(" ");
//         i++;
//     }

//     if (newline)
//         printf("\n");

//     return 0;
// }


{
	int i = 1;
	int newline = 1;
	if (args[1].value && ft_strcmp(args[1].value, "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i].value)
	{
		printf("%s", args[i].value);
		i++;
		// if (args[++i].value)
		// 	printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}

// int main(int argc, char *argv[])
// {
//	 if (argc > 1)
//		 shell_echo(&argv[1]);
//	 else
//		 printf("Usage: %s [options] [text]\n", argv[0]);
//	 return (0);
// }