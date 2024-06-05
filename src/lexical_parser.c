/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:24:36 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/04 19:54:57 by aneekhra         ###   ########.fr       */
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
    strncpy(tokens[*token_count].value, value, MAX_TOKEN_LENGTH);
    tokens[*token_count].value[MAX_TOKEN_LENGTH] = '\0'; // Ensure null termination
    tokens[*token_count].type = T_WORD;
    (*token_count)++;
}

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


// void handleWord(const char **ptr, Token *tokens, int *token_count) {
//     int len = 0;
//     while (**ptr && !isspace(**ptr) && **ptr != '|' && **ptr != '>' && **ptr != '<' && **ptr != '\'' && **ptr != '\"') {
//         tokens[*token_count].value[len++] = **ptr;
//         (*ptr)++;
//     }
//     tokens[*token_count].value[len] = '\0';
//     tokens[*token_count].type = T_WORD;
//     (*token_count)++;
// }

// void handleQuote(const char **ptr, Token *tokens, int *token_count) {
//     char quote_char = **ptr;
//     tokens[*token_count].value[0] = quote_char;
//     int len = 1;
//     (*ptr)++;
//     while (**ptr && **ptr != quote_char) {
//         tokens[*token_count].value[len++] = **ptr;
//         (*ptr)++;
//     }
//     tokens[*token_count].value[len++] = quote_char;
//     tokens[*token_count].value[len] = '\0';
//     tokens[*token_count].type = T_QUOTE;
//     (*token_count)++;
//     if (**ptr) (*ptr)++;
// }

// void handlePipe(const char **ptr, Token *tokens, int *token_count) {
//     tokens[*token_count].value[0] = **ptr;
//     tokens[*token_count].value[1] = '\0';
//     tokens[*token_count].type = T_PIPE;
//     (*token_count)++;
//     (*ptr)++;
// }

// void handleRedirection(const char **ptr, Token *tokens, int *token_count) {
//     tokens[*token_count].value[0] = **ptr;
//     if (**ptr == '>' && *(*ptr + 1) == '>') {
//         tokens[*token_count].value[1] = '>';
//         tokens[*token_count].value[2] = '\0';
//         tokens[*token_count].type = T_DGREAT;
//         (*ptr)++;
//     } else if (**ptr == '<' && *(*ptr + 1) == '<') {
//         tokens[*token_count].value[1] = '<';
//         tokens[*token_count].value[2] = '\0';
//         tokens[*token_count].type = T_DLESS;
//         (*ptr)++;
//     } else {
//         tokens[*token_count].value[1] = '\0';
//         tokens[*token_count].type = (**ptr == '>') ? T_RED_TO : T_RED_FROM;
//     }
//     (*token_count)++;
//     (*ptr)++;
// }