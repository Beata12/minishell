/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:25:21 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/04 14:31:58 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

// int shell_rm(Token tokens[], int token_count)
// {
//     int i;

//     i = 1;
//      if (tokens == NULL) {
//         fprintf(stderr, "Error: tokens array is NULL.\n");
//         return 1;
//     }
//     if (token_count < 2)
//     {
//         fprintf(stderr, "Usage: rm <filename>\n");
//         return 1;
//     }
//     while (i < token_count) {
//         if (unlink(tokens[i].value) == -1) {
//             perror("unlink");
//             return 1;
//         }
//         i++;
//     }
//     return 0; // Success
// }

int shell_rm(Token tokens[], int token_count) {
    if (tokens == NULL) {
        fprintf(stderr, "Error: tokens array is NULL.\n");
        return 1;
    }

    if (token_count < 2) {
        fprintf(stderr, "Usage: rm <file>...\n");
        return 1;
    }

    for (int i = 1; i < token_count; i++) {
        if (unlink(tokens[i].value) == -1) {
            fprintf(stderr, "Error removing file %s: %s\n", tokens[i].value, strerror(errno));
            return 1;
        }
    }

    return 0; // Success
}

int shell_rmdir(Token tokens[], int token_count) {
    if (tokens == NULL) {
        fprintf(stderr, "Error: tokens array is NULL.\n");
        return 1;
    }

    if (token_count < 2) {
        fprintf(stderr, "Usage: rmdir <directory>...\n");
        return 1;
    }

    for (int i = 1; i < token_count; i++) {
        if (rmdir(tokens[i].value) == -1) {
            fprintf(stderr, "Error removing directory %s: %s\n", tokens[i].value, strerror(errno));
            return 1;
        }
    }

    return 0; // Success
}