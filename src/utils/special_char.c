/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:58:35 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/06 14:45:35 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error_msg_pipe(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && str[i] != '|'))
			dif = 1;
		if (str[i] == '|')
		{
			if (dif == 0)
			{
				if (ft_strnstr(str, "||", ft_strlen(str)) != NULL)
					ft_putstr_fd("minishell: \
syntax error near unexpected token '||' \n",
									2);
				else if (ft_strnstr(str, "|", ft_strlen(str)) != NULL)
					ft_putstr_fd("minishell: \
syntax error near unexpected token '|' \n",
									2);
				return (1);
			}
			dif = 0;
		}
		i++;
	}
	return (0);
}

int	print_error_msg_ampresent(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && str[i] != '&'))
			dif = 1;
		if (str[i] == '&')
		{
			if (dif == 0)
			{
				if (ft_strnstr(str, "&&", ft_strlen(str)) != NULL)
					ft_putstr_fd("minishell: \
syntax error near unexpected token '&&' \n",
									2);
				else if (ft_strnstr(str, "&", ft_strlen(str)) != NULL)
					ft_putstr_fd("minishell: \
syntax error near unexpected token '&' \n",
									2);
				return (1);
			}
			dif = 0;
		}
		i++;
	}
	return (0);
}

int	print_error_msg_closing_brace(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && str[i] != ')'))
			dif = 1;
		if (str[i] == ')')
		{
			if (dif == 0)
			{
				ft_putstr_fd("minishell: \
syntax error near unexpected token ')' \n",
								2);
				return (1);
			}
			dif = 0;
		}
		i++;
	}
	return (0);
}

int	print_error_msg_closing_square(char *str)
{
	if (ft_strcmp(str, "]]"))
	{
		ft_putstr_fd("minishell: \
syntax error near unexpected token ']]' \n",
						2);
		return (1);
	}
	return (0);
}

int	print_error_msg_closing_curly(char *str)
{
	if (ft_strcmp(str, "}"))
	{
		ft_putstr_fd("minishell: \
syntax error near unexpected token '}' \n",
						2);
		return (1);
	}
	return (0);
}
