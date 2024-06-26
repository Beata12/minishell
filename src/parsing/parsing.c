/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:26:11 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/07 22:16:08 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int	parse_input(char *input)
{
	t_args	shell_data;

	if (wrong_input(&shell_data, input))
		return (0);
	remove_extra_spaces(input);
	split_token();
	return (1);
}

// Simple lexical function (lexer) for tokenizing input
// int	lex(const char *input, Token *tokens)
// {
// 	int			token_count;
// 	const char	*ptr = input;
// 	int			in_quotes;

// 	token_count = 0;
// 	in_quotes = 0;
// 	while (*ptr != '\0')
// 	{
// 		if (!in_quotes && isspace(*ptr))
// 		{
// 			ptr++;
// 			continue ;
// 		}
// 		else if (*ptr == '\"' || *ptr == '\'')
// 			handleQuote(&ptr, tokens, &token_count);
// 		else if (*ptr == '|')
// 			handlePipe(&ptr, tokens, &token_count);
// 		else if (*ptr == '\\' || *ptr == ';')
// 			handleSpecial(&ptr);
// 		else
// 			handleWord(&ptr, tokens, &token_count);
// 	}
// 	return (token_count);
// }

// // Function to print token information
// void	print_token_info(Token *tokens, int token_count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < token_count)
// 	{ // Loop through tokens
// 		printf("Token %d: type: ", i + 1);
// 		if (tokens[i].type == T_WORD)
// 		{
// 			printf("WORD");
// 		} // Print token type
// 		else if (tokens[i].type == T_RED_TO)
// 		{
// 			printf("RED_TO");
// 		}
// 		else if (tokens[i].type == T_RED_FROM)
// 		{
// 			printf("RED_FROM");
// 		}
// 		else if (tokens[i].type == T_DLESS)
// 		{
// 			printf("DLESS");
// 		}
// 		else if (tokens[i].type == T_DGREAT)
// 		{
// 			printf("DGREAT");
// 		}
// 		else if (tokens[i].type == T_PIPE)
// 		{
// 			printf("PIPE");
// 		}
// 		else if (tokens[i].type == T_QUOTE)
// 		{
// 			printf("QUOTE");
// 		}
// 		else
// 		{
// 			printf("ERROR");
// 		}
// 		printf(", value: %s\n", tokens[i].value); // Print token value
// 		i++;                                      // Increment counter
// 	}
// }

// int	parse_input(char *input)
// {
// 	// if (wrong_input(input))
// 	return (0);
// }

// // Function to parse the command
// void	parser(char *input_command)
// {
// 	int i;
// 	i = 1;
// 	Token tokens[1024];
// 	int token_count = lex(input_command, tokens); // Tokenize the input command
// 													// print_token_info(tokens,token_count);
// 													// Print information about tokens
// 	// ft_execvp(tokens[0].value, tokens); // Execute the command
// 	handle_redirection(input_command); // Obsługa przekierowań
// 	// ft_execvp(input_command, tokens[i].value);

// 	if (token_count > 0 && strcmp(tokens[0].value, "echo") == 0)
// 		shell_echo(tokens);
// 	else if (token_count > 0 && strcmp(tokens[0].value, "exit") == 0)
// 		shell_exit(tokens);
// 	else if (token_count > 0 && strcmp(tokens[0].value, "pwd") == 0)
// 		shell_pwd(tokens);
// 	else if (token_count > 0 && strcmp(tokens[0].value, "env") == 0)
// 		shell_env();
// 	else if (token_count > 0 && strcmp(tokens[0].value, "cd") == 0)
// 		shell_cd(tokens);
// 	else if (token_count > 0 && strcmp(tokens[0].value, "export") == 0)
// 		shell_export(tokens);
// 	else if (token_count > 0 && strcmp(tokens[0].value, "unset") == 0)
// 		shell_unset(tokens);
// 	// else if (token_count > 0 && strcmp(tokens[0].value, "ls") == 0)
// 	//     shell_ls(tokens, token_count);
// 	// else if (token_count > 0 && strcmp(tokens[0].value, "touch") == 0)
// 	// 	shell_touch(tokens, token_count);
// 	// else if (token_count > 0 && strcmp(tokens[0].value, "rm") == 0)
// 	// 	shell_rm(tokens, token_count);
// 	// else if (token_count > 0 && strcmp(tokens[0].value, "mkdir") == 0)
// 	// 	shell_mkdir(tokens, token_count);
// 	// else if (token_count > 0 && strcmp(tokens[0].value, "clear") == 0)
// 	// 	shell_clear();
// 	// else if (token_count > 0 && strcmp(tokens[0].value, "rmdir") == 0)
// 	//     shell_rmdir(tokens, token_count);
// 	else
// 		printf("Command '%s' not found.\n", input_command);
// }