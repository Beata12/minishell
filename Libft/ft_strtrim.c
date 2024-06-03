/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:59:25 by aneekhra          #+#    #+#             */
/*   Updated: 2023/11/29 16:55:38 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*str;
	int		len;
	int		j;

	i = 0;
	len = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	len = ft_strlen(s1);
	while (i < len && ft_strrchr((char *)set, s1[len - 1]))
		len--;
	str = (char *)malloc((sizeof(char)) * (len - i + 1));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (s1[i] && i < len)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
