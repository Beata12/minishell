/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:15:38 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 12:48:55 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int shell_touch(Token tokens[], int token_count)
{
    int i;

    i = 1;
    if (token_count < 2)
    {
        fprintf(stderr, "Usage: touch <filename>\n");
        return 1;
    }
    while (i < token_count)
    {
        // Create or open with write access and default permissions
        int fd = open(tokens[i].value, O_CREAT | O_WRONLY, 0644);
        if (fd == -1)
        {
            perror("open");
            return 1;
        }
        close(fd); // Close the file descriptor
        i++;
    }
    return 0; // Success
}