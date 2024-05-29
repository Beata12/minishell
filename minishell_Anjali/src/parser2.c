/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:57:28 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/29 17:59:52 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

// Simple lexical function (lexer) for tokenizing input
int lex(const char *input, Token *tokens)
{
    int token_count;   // Counter for tokens
    const char *ptr = input;   // Pointer to traverse the input string

	token_count = 0;
    while (*ptr != '\0') // Loop until the end of the input string
	{
        // Skip whitespace
        while (isspace(*ptr))
		{
            printf("Whitespace found, skipping...\n");
            ptr++;
        }
        if (*ptr == '\0')
			break;  // Break if end of string
        if (*ptr == '|')
		{
            // Handle pipe character
            printf("Pipe found, adding token...\n");
            tokens[token_count].type = T_PIPE;
            tokens[token_count].value[0] = *ptr;
            tokens[token_count].value[1] = '\0';
            ptr++;
        }
		else if (*ptr == '"') {
            // Handle double quotes
            printf("Double quote found, processing...\n");
            tokens[token_count].type = T_QUOTE;
            int len = 0;
            ptr++; // Skip the starting quote
            while (*ptr != '\0' && *ptr != '"' && len < 255)
			{
                if (*ptr == '$')
				{
                    // Handle environment variables inside double quotes
                    tokens[token_count].value[len++] = *ptr++;
                    while (isalnum(*ptr) || *ptr == '_')
                        tokens[token_count].value[len++] = *ptr++;
                }
				else
                    tokens[token_count].value[len++] = *ptr++;
            }
            if (*ptr == '"')
			{
                printf("End double quote found, adding token: \"%s\"\n", tokens[token_count].value);
                ptr++; // Skip the ending quote
            }
			else
			{
                // Handle unclosed double quote
                fprintf(stderr, "Error: Unclosed double quote detected\n");
                return 0;
            }
            tokens[token_count].value[len] = '\0';
        }
		else if (*ptr == '\'')
		{
            // Handle single quotes
            printf("Single quote found, processing...\n");
            tokens[token_count].type = T_QUOTE;
            int len = 0;
            ptr++; // Skip the starting quote
            while (*ptr != '\0' && *ptr != '\'' && len < 255)
                tokens[token_count].value[len++] = *ptr++;
            if (*ptr == '\'')
			{
                printf("End single quote found, adding token: '%s'\n", tokens[token_count].value);
                ptr++; // Skip the ending quote
            }
			else
			{
                // Handle unclosed single quote
                fprintf(stderr, "Error: Unclosed single quote detected\n");
                return 0;
            }
            tokens[token_count].value[len] = '\0';
        }
		else if (*ptr == '\\' || *ptr == ';')
		{
            // Ignore backslash and semicolon characters
            printf("Ignoring special character: %c\n", *ptr);
            ptr++;
        }
		else
		{
            // Handle words
            int len = 0;
            while (*ptr != '\0' && !isspace(*ptr) && *ptr != '|' && *ptr != '"' && *ptr != '\'' && *ptr != '\\' && *ptr != ';' && len < 255)
                tokens[token_count].value[len++] = *ptr++;
            tokens[token_count].value[len] = '\0';
            tokens[token_count].type = T_WORD;
            printf("Processing word: %s\n", tokens[token_count].value);
        }
        token_count++;
    }
    return token_count; // Return the number of tokens
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
    print_token_info(tokens, token_count); // Print information about tokens
    if (token_count > 0 && my_strcmp(tokens[0].value, "echo") == 0)
	{
        // Handle echo command
        printf("Echoing:");
        while (i < token_count)
		{ // Loop through tokens starting from index 1
			printf(" %s", tokens[i].value); // Print token value
			i++; // Increment counter
		}
        printf("\n");
    }
	else// Placeholder for parsing other commands
        printf("Other command parsing is not implemented yet.\n");
}
