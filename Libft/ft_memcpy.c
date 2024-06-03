/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:11:26 by aneekhra          #+#    #+#             */
/*   Updated: 2023/11/29 16:57:27 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *d, const void *s, size_t len)
{
	size_t	i;
	char	*src;
	char	*dest;

	i = 0;
	src = (char *)s;
	dest = (char *)d;
	if (len == 0)
		return (dest);
	if (!src && !dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
