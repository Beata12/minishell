/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:24:36 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/31 12:25:08 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    printf("Processing word: %s\n", tokens[*token_count].value);
    (*token_count)++;
}

void handleQuote(const char **ptr, Token *tokens, int *token_count)
{
    printf("%c quote found, processing...\n", **ptr);
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
        printf("End %c quote found, adding token: \"%s\"\n", quote_char, tokens[*token_count].value);
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
