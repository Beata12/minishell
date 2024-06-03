/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:33:34 by aneekhra          #+#    #+#             */
/*   Updated: 2023/11/25 00:16:08 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big_str, char *small, size_t len)
{
	size_t	i;
	size_t	n_len;
	size_t	j;

	n_len = ft_strlen(small);
	if (small[0] == '\0')
		return ((char *)big_str);
	i = 0;
	while (big_str[i] && i < len)
	{
		j = 0;
		while (big_str[i + j] && small[j] && (i + j) < len
			&& big_str[i + j] == small[j])
			j++;
		if (j == n_len)
			return ((char *)(big_str + i));
		i++;
	}
	return (NULL);
}
