/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:09:26 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/04 21:32:08 by aneekhra         ###   ########.fr       */
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
		if (isspace(*ptr))
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
void execute_command(Token *tokens, int token_count)
{
	if (token_count > 0 && strcmp(tokens[0].value, "echo") == 0)
		shell_echo(tokens);
	else if(token_count > 0 && strcmp(tokens[0].value, "exit") == 0)
		shell_exit(tokens);
	else if(token_count > 0 && strcmp(tokens[0].value, "pwd") == 0)
		shell_pwd(tokens);
	else if(token_count > 0 && strcmp(tokens[0].value, "env") == 0)
		shell_env();
	else if(token_count > 0 && strcmp(tokens[0].value, "cd") == 0)
		shell_cd(tokens);
	else if(token_count > 0 && strcmp(tokens[0].value, "export") == 0)
		shell_export(tokens);
	else if(token_count > 0 && strcmp(tokens[0].value, "unset") == 0)
		shell_unset(tokens);
	else if (token_count > 0 && strcmp(tokens[0].value, "ls") == 0)
        shell_ls(tokens, token_count);
	else if (token_count > 0 && strcmp(tokens[0].value, "touch") == 0)
    	shell_touch(tokens, token_count);
	else if (token_count > 0 && strcmp(tokens[0].value, "rm") == 0)
    	shell_rm(tokens, token_count);
	else if (token_count > 0 && strcmp(tokens[0].value, "mkdir") == 0)
    	shell_mkdir(tokens, token_count);
	else if (token_count > 0 && strcmp(tokens[0].value, "clear") == 0)
    	shell_clear();
	else if (token_count > 0 && strcmp(tokens[0].value, "rmdir") == 0) 
        shell_rmdir(tokens, token_count);
	else if (token_count > 0 && strcmp(tokens[0].value, "") == 0)
		return ;
}

// Function to parse the command
void parser(char *input_command)
{
	int i;
	int status;
	Token tokens[1024];
	
	i = 0;
	int token_count = lex(input_command, tokens); // Tokenize the input command
	if(token_count == 0)
		return ;
	
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child process
        while (i < token_count)
        {
            if (tokens[i].type == T_PIPE)
            {
				handle_heredoc(tokens, token_count);
                break;
            }
            i++;
        }
  		handle_redirection(tokens, token_count); // Obsługa przekierowań
        execute_command(tokens, token_count);
        exit(0);
    }
    else if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else
    {
		int status;
        waitpid(pid, &status, WUNTRACED);
	}
}
