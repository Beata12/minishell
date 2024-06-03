/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:24:36 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 15:45:25 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

void handleWord(const char **ptr, Token *tokens, int *token_count)
{
	const int MAX_TOKEN_LENGTH = 255; 
	char value[MAX_TOKEN_LENGTH + 1];
	int len = 0;

	while (**ptr != '\0' && !isspace(**ptr) && **ptr != '|' && **ptr != '"'
		&& **ptr != '\'' && **ptr != '\\' && **ptr != ';' && len < MAX_TOKEN_LENGTH)
	{
		value[len++] = **ptr;
		(*ptr)++;
	}
	value[len] = '\0';
	strcpy(tokens[*token_count].value, value);
	tokens[*token_count].type = T_WORD;
	//printf("Processing word: %s\n", tokens[*token_count].value);
	(*token_count)++;
}
// void handleWord(const char **ptr, Token *tokens, int *token_count)
// {
//	 const int INITIAL_BUFFER_SIZE = 256; // Start with an initial buffer size
//	 int buffer_size = INITIAL_BUFFER_SIZE;
//	 char *value2 = (char *)malloc(buffer_size * sizeof(char));
//	 if (value2 == NULL) {
//		 fprintf(stderr, "Error: Memory allocation failed\n");
//		 return;
//	 }
//	 int len = 0;

//	 while (**ptr != '\0' && !isspace(**ptr) && **ptr != '|' && **ptr != '"'
//			&& **ptr != '\'' && **ptr != '\\' && **ptr != ';')
//	 {
//		 if (len >= buffer_size - 1) {
//			 buffer_size *= 2; // Double the buffer size
//			 char *new_value2 = (char *)realloc(value2, buffer_size * sizeof(char));
//			 if (new_value2 == NULL) {
//				 free(value2);
//				 fprintf(stderr, "Error: Memory reallocation failed\n");
//				 return;
//			 }
//			 value2 = new_value2;
//		 }
//		 value2[len++] = **ptr;
//		 (*ptr)++;
//	 }
//	 value2[len] = '\0';

//	 // Allocate memory for the token value2 and copy the string
//	 tokens[*token_count].value2 = (char *)malloc((len + 1) * sizeof(char));
//	 if (tokens[*token_count].value2 == NULL) {
//		 free(value2);
//		 fprintf(stderr, "Error: Memory allocation failed for token value2\n");
//		 return;
//	 }
//	 strcpy(tokens[*token_count].value2, value2);
//	 tokens[*token_count].type = T_WORD;

//	 free(value2);  // Free the intermediate buffer
//	 (*token_count)++;
// }

void handleQuote(const char **ptr, Token *tokens, int *token_count)
{
   // printf("%c quote found, processing...\n", **ptr);
	tokens[*token_count].type = T_QUOTE;
	int len = 0;
	char quote_char = **ptr;
	(*ptr)++;
	while (**ptr != '\0' && **ptr != quote_char) 
	{
		tokens[*token_count].value[len++] = **ptr;
		(*ptr)++;
	}
	if (**ptr == quote_char)
	{
	   // printf("End %c quote found, adding token: \"%s\"\n", quote_char, tokens[*token_count].value);
		(*ptr)++;
	}
	else
	{
		fprintf(stderr, "Error: Unclosed %c quote detected\n", quote_char);
		return;
	}
	tokens[*token_count].value[len] = '\0';
	(*token_count)++;
}

void handlePipe(const char **ptr, Token *tokens, int *token_count)
{
	printf("Pipe found, adding token...\n");
	tokens[*token_count].type = T_PIPE;
	tokens[*token_count].value[0] = **ptr;
	tokens[*token_count].value[1] = '\0';
	(*ptr)++;
	(*token_count)++;
}
void handleSpecial(const char **ptr)
{
	printf("Ignoring special character: %c\n", **ptr);
	(*ptr)++;
}

int	check_str(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			return (print_error_msg_pipe(input));
		else if (input[i] == '&')
			return (print_error_msg_ampresent(input));
		else if (input[i] == ')')
			return (print_error_msg_closing_brace(input));
		else if (input[i] == ']')
			return (print_error_msg_closing_square(input));
		else if (input[i] == '}')
			return (print_error_msg_closing_curly(input));
		i++;
	}
	return (0);
}
