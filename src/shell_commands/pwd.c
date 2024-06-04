/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:56 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 21:29:37 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int shell_pwd(Token *argv)
{
	if (argv == NULL)
		return (0);
	char *cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

// typedef struct {
//     char *value2; // Use a pointer for dynamic allocation
// 	char value[256];// Value of the token, assuming max length 256 characters
//     int type;
// } Token;

// void parser(char *input_command)
// {
// 	int i;
// 	i = 1;
// 	Token tokens[1024];
// 	int token_count = lex(input_command, tokens); // Tokenize the input command
//     if(token_count > 0 && strcmp(tokens[0].value, "pwd") == 0)
// 		shell_pwd(tokens);
// 	else// Placeholder for parsing other commands
// 		return;
// 		// printf("Other command parsing is not implemented yet.\n");
// }