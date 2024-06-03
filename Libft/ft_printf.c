/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:47:11 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/14 14:12:40 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkarg(const char *in_str, va_list	str_list)
{
	int		f;

	f = 0;
	if (in_str[0] == 'c')
		f = ft_putchar((int) va_arg(str_list, int));
	else if (in_str[0] == 's')
		f = ft_putstr(va_arg(str_list, char *));
	else if (in_str[0] == 'p')
		f = ft_putptr(va_arg(str_list, unsigned long));
	else if (in_str[0] == 'd' || in_str[0] == 'i')
		f = ft_putnbr(va_arg(str_list, int));
	else if (in_str[0] == 'u')
		f = ft_putunbr(va_arg(str_list, unsigned int));
	else if (in_str[0] == 'x')
		f = ft_puthexa_low(va_arg(str_list, unsigned int));
	else if (in_str[0] == 'X')
		f = ft_puthexa_up(va_arg(str_list, unsigned int));
	else if (in_str[0] == '%')
		f = ft_putchar('%');
	return (f);
}

int	ft_printf(const char *in_str, ...)
{
	va_list	str_list;
	int		i;
	int		f;
	int		c;

	i = -1;
	f = 0;
	c = 0;
	va_start(str_list, in_str);
	while (in_str[++i])
	{
		if (in_str[i] == '%' && in_str[++i])
		{
			c = ft_checkarg(&in_str[i], str_list);
		}
		else
			c = ft_putchar(in_str[i]);
		if (c == -1)
			return (-1);
		f += c;
	}
	return (f);
}
