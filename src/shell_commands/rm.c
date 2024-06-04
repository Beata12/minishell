/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:25:21 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 12:48:55 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int shell_rm(Token tokens[], int token_count)
{
    int i;

    i = 1;
    if (token_count < 2)
    {
        fprintf(stderr, "Usage: rm <filename>\n");
        return 1;
    }
    while (i < token_count) {
        if (unlink(tokens[i].value) == -1) {
            perror("unlink");
            return 1;
        }
        i++;
    }
    return 0; // Success
}