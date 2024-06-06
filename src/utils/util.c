/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:27:41 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/06 14:43:20 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	my_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
int	ft_strcmp(char *str, char *in)
{
	int	len_str;
	int	len_in;
	int	i;

	i = 0;
	len_str = 0;
	len_in = 0;
	len_str = ft_strlen(str);
	len_in = ft_strlen(in);
	if (len_str != len_in)
		return (0);
	while (i < len_in)
	{
		if (str[i] != in[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] != '\0' && len != 0)
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0' && (i
				+ j) < len)
		{
			j++;
		}
		if (needle[j] == '\0')
		{
			return ((char *)&haystack[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != 0)
		i++;
	return (i);
}
void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putstr_minus_fd(char *s, int len, int fd)
{
	int	i;

	i = 0;
	while (s && s[i] && i < len)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
