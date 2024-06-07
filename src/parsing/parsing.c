/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:46:17 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/07 16:29:41 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

// Simple lexical function (lexer) for tokenizing input
int	lex(const char *input, Token *tokens)
{
	int			token_count;
	const char	*ptr = input;
	int			in_quotes;

	token_count = 0;
	in_quotes = 0;
	while (*ptr != '\0')
	{
		if (!in_quotes && isspace(*ptr))
		{
			ptr++;
			continue ;
		}
		else if (*ptr == '\"' || *ptr == '\'')
			handleQuote(&ptr, tokens, &token_count);
		else if (*ptr == '|')
			handlePipe(&ptr, tokens, &token_count);
		else if (*ptr == '\\' || *ptr == ';')
			handleSpecial(&ptr);
		else
			handleWord(&ptr, tokens, &token_count);
	}
	return (token_count);
}

// Function to print token information
void	print_token_info(Token *tokens, int token_count)
{
	int	i;

	i = 0;
	while (i < token_count)
	{ // Loop through tokens
		printf("Token %d: type: ", i + 1);
		if (tokens[i].type == T_WORD)
		{
			printf("WORD");
		} // Print token type
		else if (tokens[i].type == T_RED_TO)
		{
			printf("RED_TO");
		}
		else if (tokens[i].type == T_RED_FROM)
		{
			printf("RED_FROM");
		}
		else if (tokens[i].type == T_DLESS)
		{
			printf("DLESS");
		}
		else if (tokens[i].type == T_DGREAT)
		{
			printf("DGREAT");
		}
		else if (tokens[i].type == T_PIPE)
		{
			printf("PIPE");
		}
		else if (tokens[i].type == T_QUOTE)
		{
			printf("QUOTE");
		}
		else
		{
			printf("ERROR");
		}
		printf(", value: %s\n", tokens[i].value); // Print token value
		i++;                                      // Increment counter
	}
}

// int	parse_input(char *input)
// {
// 	// if (wrong_input(input))
// 	return (0);
// }

// Function to parse the command
char	*parser(char *input_command)
{
	int		i;
	Token	tokens[1024];
	char	*result;
	int		result_len;

	int token_count = lex(input_command, tokens); // Tokenize the input command
	result = NULL;
	result_len = 0;
	if (token_count > 0)
	{
		for (i = 0; i < token_count; i++)
		{
			result_len += strlen(tokens[i].value) + 1;
			//+1 for space or null terminator
		}
		// Allocate memory for the result string
		result = (char *)malloc(result_len + 1); // +1 for null terminator
		if (!result)
		{
			perror("malloc");
			return (NULL);
		}
		result[0] = '\0'; // Initialize the result string
		// Concatenate token values into the result string
		for (i = 0; i < token_count; i++)
		{
			strcat(result, tokens[i].value);
			if (i < token_count - 1)
			{
				strcat(result, " "); // Add space between tokens
			}
		}
	}
	return (result);
}

// {
// 	i = 0;
// 	while (i < token_count)
// 	{
// 		// printf("Token count: %s\n", tokens[i].value);
// 		// Print token count
// 		printf("%s ", tokens[i].value); // Print token value
// 		// return (tokens[i].value);
// 		i++;
// 	}
// 	return (tokens[i].value);
// }

// ft_execvp(tokens[0].value, tokens); // Execute the command
// handle_redirection(input_command); // Obsługa przekierowań
// ft_execvp(input_command, tokens[i].value);

// if (token_count > 0 && strcmp(tokens[0].value, "echo") == 0)
// 	shell_echo(tokens);
// else if (token_count > 0 && strcmp(tokens[0].value, "exit") == 0)
// 	shell_exit(tokens);
// else if (token_count > 0 && strcmp(tokens[0].value, "pwd") == 0)
// 	shell_pwd(tokens);
// else if (token_count > 0 && strcmp(tokens[0].value, "env") == 0)
// 	shell_env();
// else if (token_count > 0 && strcmp(tokens[0].value, "cd") == 0)
// 	shell_cd(tokens);
// else if (token_count > 0 && strcmp(tokens[0].value, "export") == 0)
// 	shell_export(tokens);
// else if (token_count > 0 && strcmp(tokens[0].value, "unset") == 0)
// 	shell_unset(tokens);

// else
// 	printf("Command '%s' not found.\n", input_command);
// return (0);
// }