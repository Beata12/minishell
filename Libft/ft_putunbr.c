/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:47:58 by aneekhra          #+#    #+#             */
/*   Updated: 2024/04/26 18:48:01 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int nb)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	if (nb > 9)
	{
		f = ft_putnbr(nb / 10);
		if (f == -1)
			return (-1);
		i = i + f;
		f = ft_putnbr(nb % 10);
		if (f == -1)
			return (-1);
		i = i + f;
	}
	else
	{
		if (ft_putchar(nb + '0') == -1)
			return (-1);
		i++;
	}
	return (i);
}
