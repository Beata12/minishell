/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:38 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/07 21:14:50 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*expand_variable(const char *str)
{
	const char	*var_name = str + 1;
	char		*value;

	if (str[0] == '$')
	{
		value = getenv(var_name);
		if (value)
			return (value);
	}
	return ((char *)str);
}

int	shell_echo(Token *args)
{
	int		i;
	int		newline;
	char	*expanded_value;

	i = 1;
	newline = 1;
	if (args[i].value[0] != '\0' && strcmp(args[i].value, "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i].value[0] != '\0')
	{
		expanded_value = expand_variable(args[i].value);
		printf("%s", expanded_value);
		if (args[++i].value[0] != '\0')
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}

// int shell_echo(Token *args)
// {
//     int i = 1;
//     int newline = 1;

//     if (args[i].value[0] != '\0' && strcmp(args[i].value, "-n") == 0)
//     {
//         newline = 0;
//         i++;
//     }
//     while (args[i].value[0] != '\0')
//     {
//         char *expanded_value = expand_variable(args[i].value);
//         printf("%s", expanded_value);
//         if (args[++i].value[0] != '\0')
//             printf(" ");
//     }
//     if (newline)
//         printf("\n");
//     return (0);
// }

// int shell_echo(Token tokens[], int token_count)
// {
// 	int i;

// 	i = 1;
// 	while (i < token_count)
// 	{
// 		printf("%s ", tokens[i].value);
// 		i++;
// 	}

//   printf("\n");
//   return (0); // Success
// }

// int	main(int argc, char *argv)
// {
// 	shell_echo(argv[1]);

// 	return (0);
// }