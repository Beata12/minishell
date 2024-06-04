/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:55:10 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 13:01:25 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int shell_mkdir(Token tokens[], int token_count)
{
    int i;

    i = 1;
    if (token_count < 2)
    {
        fprintf(stderr, "Usage: mkdir <directory_name>\n");
        return 1;
    }
    while (i < token_count) {
        if (mkdir(tokens[i].value, 0755) == -1)
        {
            perror("mkdir");
            return 1;
        }
        i++;
    }
    return 0;
}