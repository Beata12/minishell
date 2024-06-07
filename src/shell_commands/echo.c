/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:38 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/07 21:23:46 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

char	*expand_variable(const char *str)
{
	char	*value;

	if (str[0] == '$')
	{
		const char *var_name = str + 1; // Skip the '$' character
		value = getenv(var_name);
		if (value)
		{
			return (value);
		}
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
		{
			printf(" ");
		}
	}
	if (newline)
	{
		printf("\n");
	}
	return (0);
}

int	main(int argc, char **argv)
{
	Token	tokens[1024];
	int		i;

	// Populate tokens array with command line arguments
	for (i = 0; i < argc; i++)
	{
		tokens[i].value2 = argv[i];
	}
	// Ensure the tokens array is null-terminated
	tokens[argc].value2 = "";
	// Call shell_echo with the tokens
	shell_echo(tokens);
	return (0);
}

// int shell_echo(Token tokens[], int token_count)
// {
// 	int i;

// 	i = 1;
// 	while (i < token_count)
// 	{
// 		printf("%s ", tokens[i].value);
// 		i++;
// 	}

//     printf("\n");
//     return (0); // Success
// }
