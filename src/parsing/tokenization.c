/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:53:07 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/07 13:42:55 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_types	token_type(char *token)
{
	if (*token == '|')
		return (T_PIPE);
	else if (*token == '<')
		return (T_RED_FROM);
	else if (*token == '>')
		return (T_RED_TO);
	else if (*token == *(token + 1) && *token == '<')
		return (T_DLESS);
	else if (*token == *(token + 1) && *token == '>')
		return (T_DGREAT);
	else
		return (T_WORD);
}