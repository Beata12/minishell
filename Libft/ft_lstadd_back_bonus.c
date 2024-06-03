/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:21:17 by aneekhra          #+#    #+#             */
/*   Updated: 2023/11/30 17:11:11 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	last_node = *lst;
	if (new)
	{
		if (last_node == NULL)
			*lst = new;
		else
		{
			while (last_node->next != NULL)
				last_node = last_node->next;
			last_node->next = new;
		}
	}
}
