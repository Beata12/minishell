/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:35:00 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 12:39:21 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int shell_clear(void)
{
    if (system("clear") == -1) {
        perror("system");
        return 1;
    }
    return 0;
}