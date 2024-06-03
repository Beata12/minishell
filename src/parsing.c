/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 07:43:12 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 21:00:06 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

// Simple lexical function (lexer) for tokenizing input
int lex(const char *input, Token *tokens)
{
	int token_count = 0;
	const char *ptr = input;
	int in_quotes = 0;

	while (*ptr != '\0')
	{
		if (!in_quotes && isspace(*ptr))
		{
			ptr++;
			continue;
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
	return token_count;
}

// Function to print token information
void print_token_info(Token *tokens, int token_count)
{
	int i;

	i = 0;
	while (i < token_count)
	{ // Loop through tokens
		printf("Token %d: type: ", i + 1);
		if (tokens[i].type == T_WORD) { printf("WORD"); } // Print token type
		else if (tokens[i].type == T_RED_TO) { printf("RED_TO"); }
		else if (tokens[i].type == T_RED_FROM) { printf("RED_FROM"); }
		else if (tokens[i].type == T_DLESS) { printf("DLESS"); }
		else if (tokens[i].type == T_DGREAT) { printf("DGREAT"); }
		else if (tokens[i].type == T_PIPE) { printf("PIPE"); }
		else if (tokens[i].type == T_QUOTE) { printf("QUOTE"); }
		else { printf("ERROR"); }
		printf(", value: %s\n", tokens[i].value); // Print token value
		i++; // Increment counter
	}
}

// Function to parse the command
void parser(char *input_command)
{
	int i;
	i = 1;
	Token tokens[1024];
	int token_count = lex(input_command, tokens); // Tokenize the input command
   // print_token_info(tokens, token_count); // Print information about tokens
	//ft_execvp(tokens[0].value, tokens); // Execute the command
	handle_redirection(input_command); // Obsługa przekierowań
	// ft_execvp(input_command, tokens[i].value);
	if (token_count > 0 && strcmp(tokens[0].value, "echo") == 0)
	{
		// Handle echo command
		//printf("Echoing:");
		while (i < token_count)
		{ // Loop through tokens starting from index 1
			printf(" %s", tokens[i].value); // Print token value
			i++; // Increment counter
		}
		printf("\n");
	}
	else// Placeholder for parsing other commands
		return;
		// printf("Other command parsing is not implemented yet.\n");
}

// void parser(char *input_command)
// {
//	 int token_count;
// 	int i;
//	 Token tokens[1024];

// 	i = 1;
//	 if (strlen(input_command) == 0)
// 	{
//		 // Handle empty input
//		 printf("\n");
//		 return;
//	 }
//	 token_count = lex(input_command, tokens); // Tokenize the input command
//	 // print_token_info(tokens, token_count); // Print information about tokens
//	 // ft_execvp(tokens[0].value, tokens); // Execute the command
//	 handle_redirection(input_command); // Obsługa przekierowań
//	 if (token_count > 0 && strcmp(tokens[0].value, "echo") == 0)
// 	{
// 		for (int i = 1; i < token_count; i++)
//			 printf(" %s", tokens[i].value); // Print token value
// 		// while (i < token_count)
// 		// {
//		 //	 printf(" %s", tokens[i].value); // Print token value
// 		// 	i++;
// 		// }
//		 printf("\n");
//	 }
//	 else // Placeholder for parsing other commands
//		 printf("Other command parsing is not implemented yet.\n");
// }
