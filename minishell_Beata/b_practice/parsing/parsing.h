/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 07:42:37 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/30 12:32:47 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum e_token_types {
    T_WORD = 0,     // Word token
    T_RED_TO,       // Redirection to (>)
    T_RED_FROM,     // Redirection from (<)
    T_DLESS,        // Here-document (<<)
    T_DGREAT,       // Append (>>)
    T_PIPE,         // Pipe (|)
    T_QUOTE,        // Quote (single or double)
    T_ERROR         // Error token
} t_token_types;

// Structure for tokens
typedef struct {
    int type;       // Type of the token
    char value[256];// Value of the token, assuming max length 256 characters
} Token;

void	handleWord(const char **ptr, Token *tokens, int *token_count);
void	handleQuote(const char **ptr, Token *tokens, int *token_count);
void	handlePipe(const char **ptr, Token *tokens, int *token_count);
void	handleSpecial(const char **ptr);

#endif