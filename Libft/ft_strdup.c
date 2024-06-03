/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:41:07 by aneekhra          #+#    #+#             */
/*   Updated: 2023/11/25 00:17:56 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	size_t	l;
	char	*s2;

	l = ft_strlen(s1) + 1;
	s2 = malloc(l * sizeof(char));
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, l);
	return (s2);
}
