/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:06:05 by aneekhra          #+#    #+#             */
/*   Updated: 2024/04/23 14:39:58 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/libft.h"

void	executer(char *argv, char *envp[])
{
	int		i;
	char	**command;
	char	**paths;
	char	*check_cmd;

	command = ft_split(argv, ' ');
	paths = splitting_paths(envp);
	if (paths == NULL)
		ft_error("pipex: no PATH");
	i = 0;
	while (paths[i])
	{
		check_cmd = ft_strjoin_mod(paths[i], '/', command[0]);
		if (access(check_cmd, F_OK) == 0)
		{
			if (execve(check_cmd, command, NULL) == -1)
				ft_perror("ERROR");
		}
		free(check_cmd);
		i++;
	}
	ft_error_exit(command[0], ": command not found", 127);
	liberator(command);
	liberator(paths);
}

void	child1(int *fd, char *argv[], char *envp[])
{
	int	f_in;

	f_in = open(argv[1], O_RDONLY, 0777);
	if (f_in < 0)
		ft_error_exit(argv[1], ": No such file or directory", 127);
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		ft_perror("DUP2 ERROR...");
	if (dup2(f_in, STDIN_FILENO) < 0)
		ft_perror("DUP2 ERROR...");
	close(fd[0]);
	close(f_in);
	close(fd[1]);
	executer(argv[2], envp);
	ft_perror("Executer ERROR...");
}

void	child2(int *fd, char *argv[], char *envp[])
{
	int	f_out;

	f_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (f_out < 0)
		ft_error_exit(": No such file or directory\n", argv[4], 1);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		ft_perror("DUP2 ERROR...");
	if (dup2(f_out, STDOUT_FILENO) == -1)
		ft_perror("DUP2 ERROR...");
	close(fd[1]);
	close(f_out);
	close(fd[0]);
	executer(argv[3], envp);
	ft_perror("Executer ERROR...");
}

void	pipex(char *argv[], char *envp[])
{
	int	fd[2];
	int	pid1;

	if (pipe(fd) == -1)
		ft_perror("pipe failed.");
	pid1 = fork();
	if (pid1 < 0)
		ft_perror("Forking ERROR For Child 1..");
	if (pid1 == 0)
		child1(fd, argv, envp);
	waitpid(pid1, NULL, 0);
	child2(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char *argv[], char*envp[])
{
	if (argc != 5)
		return (print_error("Usage: ",
				"./pipex input_file cmd1 cmd2 output_file.", "", 1));
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[4]) == 0)
		ft_error_exit(argv[1], ": No such file or directory", 1);
	if (ft_strlen(argv[2]) == 0 || ft_strlen(argv[3]) == 0
		|| ft_strcmp(argv[2], " ") != 0 || ft_strcmp(argv[3], " ") != 0)
	{
		if ((ft_strcmp(argv[2], " ") != 0 && ft_strcmp(argv[3], " ") != 0)
			|| (ft_strlen(argv[2]) == 0 && ft_strlen(argv[3]) == 0))
		{
			write(2, "pipex: ", 7);
			write(2, argv[2], ft_strlen(argv[2]));
			write(2, ": command not found",
				ft_strlen(": command not found"));
			ft_error_exit(argv[2], ": command not found", 1);
		}
		ft_error_exit(": command not found", argv[2], 1);
	}
	pipex(argv, envp);
	return (0);
}
