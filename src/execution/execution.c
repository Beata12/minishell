/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:34:52 by beata             #+#    #+#             */
/*   Updated: 2024/06/07 22:13:08 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/minishell.h"
#include "../../include/parsing.h"

// void	ft_execute_cmd(char *argv, char *envp[])
// {
// 	int		i;
// 	char	**command;
// 	char	**paths;
// 	char	*check_cmd;

// 	command = ft_split(argv, ' ');
// 	paths = splitting_paths(envp);
// 	if (paths == NULL)
// 		printf("error");
// 	i = 0;
// 	while (paths[i])
// 	{
// 		check_cmd = ft_strjoin_mod(paths[i], '/', command[0]);
// 		if (access(check_cmd, F_OK) == 0)
// 		{
// 			if (execve(check_cmd, command, NULL) == -1)
// 				printf("error");
// 		}
// 		free(check_cmd);
// 		i++;
// 	}
// 	ft_error_exit(command[0], ": command not found", 127);
// 	liberator(command);
// 	liberator(paths);
// }

void	ft_exec_built_in(char *cmd, char **env)
{
	Token	tokens[1024];
	int		token_count;

	// token_count = lex(cmd, tokens);
	// handle_redirection(cmd);
	if (ft_strncmp(cmd, "cd", 2) == 0)
	// printf("cd\n");
	{
		printf("%", tokens);
		shell_cd(tokens);
	}
	else if (ft_strncmp(cmd, "echo", 4) == 0)
	{
		printf("now%s\n", cmd);
		shell_echo(tokens);
	}
	else if (ft_strncmp(cmd, "env", 3) == 0)
		// printf("env\n");
		shell_env();
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		// printf("exit\n");
		shell_exit(tokens);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		// printf("export\n");
		shell_export(tokens);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		// printf("pwd\n");
		shell_pwd(tokens);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		// printf("unset\n");
		shell_unset(tokens);
	else
		exit(0);
}

// void ft_execute(char **cmds, char **env, t_args *args)
void	ft_execute(char **cmds, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		i;
	int		pipes;

	i = 0;
	pipes = 0;
	while (cmds[i] != NULL)
	{
		// printf("pipes [%s]\n", cmds[i]);
		i++;
		pipes++;
	}
	i = 0;
	while (i < pipes)
	{
		if (pipe(fd) < 0)
			ft_perror("pipe failed");
		pid = fork();
		if (pid < 0)
		{
			ft_perror("fork failed");
		}
		if (pid == 0)
		{
			if (i != 0)
			{
				dup2(fd[0], 0);
				close(fd[0]);
			}
			// if (cmds[i + 1] != NULL)
			// 	dup2(fd[1], 1);
			// heardoc
			open_input_files(fd, cmds, env);
			open_output_files(fd, cmds, env);
			close(fd[1]);
			ft_exec_built_in(cmds[i], env);
			printf("here [%s]\n", cmds[i]);
			// ft_perror("execve failed");
			// exit(Exit_success);
		}
		else
		{
			waitpid(pid, NULL, 0);
			ft_execute_cmd(cmds[i], env);
			printf("external: [%s]\n", cmds[i]);
			close(fd[0]);
			close(fd[1]);
		}
		i++;
	}
}

void	ft_execute_cmd(char *argv, char *envp[])
{
	int		i;
	char	**command;
	char	**paths;
	char	*check_cmd;
	pid_t	pid;
	int		status;

	command = ft_split(argv, ' ');
	paths = splitting_paths(envp);
	if (paths == NULL)
	{
		printf("error");
		return ;
	}
	i = 0;
	while (paths[i])
	{
		check_cmd = ft_strjoin_mod(paths[i], '/', command[0]);
		if (access(check_cmd, F_OK) == 0)
		{
			pid = fork();
			if (pid == 0) // Child process
			{
				if (execve(check_cmd, command, envp) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE); // Exit if execve fails
				}
			}
			else if (pid > 0) // Parent process
			{
				waitpid(pid, &status, 0);
				// Wait for the child process to finish
				if (WIFEXITED(status))
				{
					// Check if the child exited normally
					if (WEXITSTATUS(status) == 0)
					{
						// Command executed successfully, return to main
						free(check_cmd);
						liberator(command);
						liberator(paths);
						return ;
					}
				}
				else
				{
					// Child process did not terminate normally
					printf("Child process did not terminate normally\n");
				}
			}
			else
				perror("fork");
		}
		free(check_cmd);
		i++;
	}
	ft_error_exit(command[0], ": command not found", 127);
	liberator(command);
	liberator(paths);
}

// PARSER

// #include "../../include/minishell.h"
// #include "../../include/parsing.h"

// // Simple lexical function (lexer) for tokenizing input
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

// // int	parse_input(char *input)
// // {
// // 	// if (wrong_input(input))
// // 	return (0);
// // }

// // Function to parse the command
// char	*parser(char *input_command)
// {
// 	int		i;
// 	Token	tokens[1024];
// 	char	*result;
// 	int		result_len;

// 	int token_count = lex(input_command, tokens); // Tokenize the input command
// 	result = NULL;
// 	result_len = 0;
// 	if (token_count > 0)
// 	{
// 		for (i = 0; i < token_count; i++)
// 		{
// 			result_len += strlen(tokens[i].value) + 1;
// 			//+1 for space or null terminator
// 		}
// 		// Allocate memory for the result string
// 		result = (char *)malloc(result_len + 1); // +1 for null terminator
// 		if (!result)
// 		{
// 			perror("malloc");
// 			return (NULL);
// 		}
// 		result[0] = '\0'; // Initialize the result string
// 		// Concatenate token values into the result string
// 		for (i = 0; i < token_count; i++)
// 		{
// 			strcat(result, tokens[i].value);
// 			if (i < token_count - 1)
// 			{
// 				strcat(result, " "); // Add space between tokens
// 			}
// 		}
// 	}
// 	return (result);
// }

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