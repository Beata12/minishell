/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:58:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/24 13:00:05 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_prompt(void)
{
	char *cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	printf("@minishell:%s$ ", cwd);
	free(cwd);
}


//tokenization
Token *tokenize(char *command, int *token_count)
{
	Token		*tokens = malloc(64 * sizeof(Token));
	char		*token;
	const char	*delimiters = " \t\n";
	int			count;

	count = 0;
	token = strtok(command, delimiters);
	while (token != NULL)
	{
		TokenType	type = TOKEN_UNKNOWN;
		if (strcmp(token, "|") == 0)
			type = TOKEN_PIPE;
		else if (strcmp(token, ">") == 0)
			type = TOKEN_REDIRECT_OUT;
		else if (strcmp(token, ">>") == 0)
			type = TOKEN_REDIRECT_APPEND;
		else
			type = TOKEN_WORD;
		tokens[count].type = type;
		tokens[count].value = strdup(token);
		count++;
		token = strtok(NULL, delimiters);
	}
	*token_count = count;
	return (tokens);
}

//parsing
int	parse_tokens(Token *tokens, int token_count)
{
	int	i;

	i = 0;
	while (i < token_count)
	{
		if (tokens[i].type == TOKEN_PIPE || tokens[i].type == TOKEN_REDIRECT_OUT
			|| tokens[i].type == TOKEN_REDIRECT_APPEND)
		{
			if (i == 0 || i == token_count - 1
				|| tokens[i + 1].type == TOKEN_PIPE
				|| tokens[i + 1].type == TOKEN_REDIRECT_OUT
				|| tokens[i + 1].type == TOKEN_REDIRECT_APPEND)
			{
				fprintf(stderr, "Syntax error near '%s'\n", tokens[i].value);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

//execution
void	execute_command(Token *tokens, int token_count)
{
	char	*args[64];
	int		arg_count;
	int		i;
	pid_t	pid;
	
	arg_count = 0;
	i = 0;
	while (i < token_count)
	{
		if (tokens[i].type == TOKEN_WORD)
			args[arg_count++] = tokens[i].value;
		i++;
	}
	args[arg_count] = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("fork() error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) < 0)
		{
			perror("execvp() error");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}

//main
int	main(void)
{
	char	*command;
	int		token_count;
	int		i;

	i = 0;
	while (1)
	{
		display_prompt();
		command = readline(NULL);
		if (command == NULL)
			break ;
		if (strlen(command) > 0)
		{
			add_history(command);
			Token	*tokens = tokenize(command, &token_count);
			if (parse_tokens(tokens, token_count))
			{
				if (strcmp(tokens[0].value, "echo") == 0)
					// shell_echo(&tokens[1].value);
					execute_command(tokens, token_count);
			}
			while (i < token_count)
			{
				free(tokens[i].value);
				i++;
			}
			free(tokens);
		}
		free(command);
	}
	return (0);
}
