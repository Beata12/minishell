/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:47:37 by aneekhra          #+#    #+#             */
/*   Updated: 2024/04/26 18:47:40 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putneg(int nb)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	if (nb == -2147483648)
	{
		if (ft_putstr("-2147483648") == -1)
			return (-1);
		i = 11;
	}
	else
	{
		if (ft_putchar('-') == -1)
			return (-1);
		i++;
		f = ft_putnbr(-nb);
		if (f == -1)
			return (-1);
		i = i + f;
	}
	return (i);
}

static int	ft_putpos(int nb)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	if (nb > 9)
	{
		f = ft_putpos(nb / 10);
		if (f == -1)
			return (-1);
		i = i + f;
		f = ft_putpos(nb % 10);
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

int	ft_putnbr(int nb)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	if (nb < 0)
	{
		f = ft_putneg(nb);
		if (f == -1)
			return (-1);
		i = i + f;
	}
	else
	{
		f = ft_putpos(nb);
		if (f == -1)
			return (-1);
		i = i + f;
	}
	return (i);
}
