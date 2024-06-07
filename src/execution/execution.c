/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:34:52 by beata             #+#    #+#             */
/*   Updated: 2024/06/07 12:45:55 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/minishell.h"

void	ft_perror(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_error_exit(char *str, char *str2, int status)
{
	int	i;

	i = 0;
	if (str2 == NULL)
	{
		write(2, "pipex: ", 7);
		write(2, str, ft_strlen(str));
		exit(127);
	}
	write(2, "pipex: ", 7);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	exit(status);
}

char	**splitting_paths(char *envp[])
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_mod(char const *s1, char connector, char const *s2)
{
	char	*str;
	size_t	x;
	size_t	y;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[y])
		str[x++] = s1[y++];
	str[x++] = connector;
	y = 0;
	while (s2[y])
		str[x++] = s2[y++];
	str[x] = '\0';
	return (str);
}

void	liberator(char **free_me)
{
	int	i;

	i = 0;
	while (free_me[i])
	{
		free(free_me[i]);
		i++;
	}
	free(free_me);
}

void	execute(char *argv, char *envp[])
{
	int		i;
	char	**command;
	char	**paths;
	char	*check_cmd;

	command = ft_split(argv, ' ');
	paths = splitting_paths(envp);
	if (paths == NULL)
		printf("error");
	i = 0;
	while (paths[i])
	{
		check_cmd = ft_strjoin_mod(paths[i], '/', command[0]);
		if (access(check_cmd, F_OK) == 0)
		{
			if (execve(check_cmd, command, NULL) == -1)
				printf("error");
		}
		free(check_cmd);
		i++;
	}
	ft_error_exit(command[0], ": command not found", 127);
	liberator(command);
	liberator(paths);
}

// char	*find_path(char *cmd, char *path)
// {
// 	char	*c;
// 	char	*tmp;
// 	char	**paths;
// 	int		i;
// 	int		fd;

// 	i = 0;
// 	paths = ft_split(path, ':');
// 	while (paths[i] != NULL)
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		c = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		fd = open(c, O_RDONLY);
// 		if (fd != -1)
// 		{
// 			close(fd);
// 			return (c);
// 		}
// 		free(c);
// 		i++;
// 	}
// 	return (NULL);
// }

// void execute(char *input, char **env)
// {
// 	char **cmds = ft_split(input, ' ');
// 	int i = 0;
// 	while(ft_strncmp(env[i], "PATH=", 5) != 0)
// 		i++;
// 	char *tmp = env[i];
// 	if (ft_strchr(cmds[0], '/') != NULL)
// 	{
// 		execve(cmds[0], cmds, env);
// 	}
// 	char *path = find_path(cmds[0], tmp);
// 	if (path == NULL)
// 	{
// 		printf("Command not found\n");
// 		exit(0);
// 	}
// 	execve(path, cmds, env);
// 	free(path);
// 	exit(0);
// }

void	ft_exe(char *cmd, char **env)
{
	Token	tokens[1024];
	int		token_count;

	token_count = lex(cmd, tokens);
	handle_redirection(cmd);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		// printf("cd\n");
		shell_cd(tokens);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		shell_echo(tokens);
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
	{
		execute(cmd, env);
		printf("we are here");
	}
}

// void ft_execute(char **cmds, char **env, t_args *args)
void	ft_execute(char **cmds, char **env)
{
	int fd[2];
	pid_t pid;
	int i = 0;
	int pipes = 0;
	while (cmds[i] != NULL)
	{
		i++;
		pipes++;
	}
	i = 0;

	while (i < pipes)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				dup2(fd[0], 0);
				close(fd[0]);
			}
			if (cmds[i + 1] != NULL)
				dup2(fd[1], 1);
			// Beqa
			// heardoc
			// open_input_files(args->input_files);
			// open_output_files(args->output_files);
			// close(fd[1]);
			ft_exe(cmds[i], env);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[0]);
			close(fd[1]);
			fd[0] = fd[0];
		}
		i++;
	}
}