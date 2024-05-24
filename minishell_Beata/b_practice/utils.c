/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:15:07 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/24 12:27:57 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}

int	my_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	my_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*my_strdup(char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * my_strlen(src) + 1);
	if (!(new))
		return (NULL);
	while (*src)
	{
		new[i++] = *src++;
	}
	new[i] = '\0';
	return (new);
}

char	*my_strtok(char *str, const char *delimiters)
{
	static char	*last_token = NULL;
	char		*token_start;

	if (str != NULL)
		last_token = str;
	while (*last_token != '\0' && my_strchr(delimiters, *last_token) != NULL)
		last_token++;
	if (*last_token == '\0')
		return (NULL);
	token_start = last_token;
	while (*last_token != '\0' && my_strchr(delimiters, *last_token) == NULL)
		last_token++;
	if (*last_token == '\0')
		last_token = NULL;
	else
	{
		*last_token = '\0';
		last_token++;
	}
	return (token_start);
}
