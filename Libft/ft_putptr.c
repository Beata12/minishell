/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:47:44 by aneekhra          #+#    #+#             */
/*   Updated: 2024/04/26 18:47:46 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putptrchar(unsigned long num)
{
	if (num < 10)
		return (ft_putchar(num + '0'));
	else
		return (ft_putchar(num + 87));
}

static int	ft_putptraddr(unsigned long num)
{
	int	i;
	int	f;

	i = 1;
	if (num < 16)
		return (ft_putptrchar(num));
	else
	{
		f = ft_putptraddr(num / 16);
		if (f == -1)
			return (-1);
		i = i + f;
		f = ft_putptrchar(num % 16);
		if (f == -1)
			return (-1);
	}
	return (i);
}

int	ft_putptr(unsigned long ptr)
{
	int	f;

	if (ft_putstr("0x") == -1)
		return (-1);
	f = ft_putptraddr(ptr);
	if (f == -1)
		return (-1);
	return (f + 2);
}
