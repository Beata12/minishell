/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:58:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/28 16:39:01 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #define HISTORY_FILE ".minishell_history"

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
int ft_newline(char **av)
{
	(void)av;
	printf("\n");
	return (0);
}

int ft_execvp(const char *args, char **argv)
{
	if (my_strcmp(args, "echo") == 0)
		return (shell_echo(argv));
	else if (my_strcmp(args, "env") == 0)
		return (shell_env(argv));
	else if (my_strcmp(args, "cd") == 0)
		return (shell_cd(argv));
	else if (my_strcmp(args, "exit") == 0)
		return (shell_exit(argv));
	else if (my_strcmp(args, "pwd") == 0)
		return (shell_pwd(argv));
	// else if (my_strcmp(args, "export") == 0)
	// 	return (shell_export(argv[0]));
	// 	// return (shell_export(argv));
	else if (my_strcmp(args, "unset") == 0)
		{shell_unset(argv);
		return (0);}
	else if (my_strcmp(args, "\n") == 0)
		return ft_newline(argv);
	else
		printf("command not found\n");
	return (0);
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
			if (ft_execvp(args[0], args) == 1)
			{
				perror("execvp() error");
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(NULL);
	// 	i++;
	// }
}

void load_history() 
{
	
    int n = read_history(HISTORY_FILE);
	if (n != 0) {
    	fprintf(stderr, "Error loading command history\n");}
}

void save_history() {
    write_history(HISTORY_FILE);
}

//main
int	main(void)
{
	char	*command;
	int		token_count;
	int		i;

	i = 0;
	
	load_history();
	
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
				// if (strcmp(tokens[0].value, "touch") == 0)
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
	save_history();
	return (0);
}
