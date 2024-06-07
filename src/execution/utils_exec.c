/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:42:16 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/07 16:54:53 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"
#include "../../include/minishell.h"
#include "../../include/parsing.h"

char	*find_path(char *cmd, char *path)
{
	char	*c;
	char	*tmp;
	char	**paths;
	int		i;
	int		fd;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		c = ft_strjoin(tmp, cmd);
		free(tmp);
		fd = open(c, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (c);
		}
		free(c);
		i++;
	}
	return (NULL);
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
int	open_input_files(int fd[], char **cmds, char **env)
{
	int		i;
	int		j;
	int		fd_in;
	char	*tmp;

	i = 0;
	while (cmds[i] != NULL)
	{
		// printf("here [%d]\n	", i);
		j = 0;
		while (cmds[i][j] != '\0')
		{
			if (cmds[i][j] == '<')
			{
				tmp = ft_strtrim(cmds[i], "<");
				fd_in = open(tmp, O_RDONLY, 0777);
				if (fd_in < 0)
					ft_error_exit(tmp, ": No such file or directory", 1);
				if (dup2(fd[1], STDOUT_FILENO) < 0)
					ft_perror("DUP2 ERROR...");
				if (dup2(fd_in, STDIN_FILENO) < 0)
					ft_perror("DUP2 ERROR...");
				close(fd_in);
				free(tmp);
				return (1);
			}
			j++;
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	open_output_files(int fd[], char **cmds, char **env)
{
	int		i;
	int		j;
	int		fd_out;
	char	*tmp;

	i = 0;
	while (cmds[i] != NULL)
	{
		j = 0;
		while (cmds[i][j] != '\0')
		{
			if (cmds[i][j] == '>')
			{
				tmp = ft_strtrim(cmds[i], ">");
				fd_out = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (fd_out < 0)
					ft_error_exit(tmp, ": No such file or directory", 1);
				if (dup2(fd[0], STDIN_FILENO) == -1)
					ft_perror("DUP2 ERROR...");
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_perror("DUP2 ERROR...");
				close(fd_out);
				free(tmp);
				return (1);
			}
			j++;
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}
