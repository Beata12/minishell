/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:01:38 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 12:48:55 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

int shell_ls(Token tokens[], int token_count)
{
    DIR *dir = opendir(".");
    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            if (token_count > 1 && strcmp(tokens[1].value, "-a") == 0)
                printf("%s\n", entry->d_name);
            continue;
        }
        printf("%s ", entry->d_name);
    }
    closedir(dir);
    printf("\n");
    return 0;
}
