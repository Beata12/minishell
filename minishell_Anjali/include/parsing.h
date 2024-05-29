/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 07:42:37 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/29 18:02:53 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <stdbool.h>

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

// Definicje typów tokenów
typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECTION_IN,
    TOKEN_REDIRECTION_OUT,
    TOKEN_END
} t_token_type;

typedef struct Token1
{
    int		type;
    char	value[256];
}				Token;


// Struktura tokena
typedef struct s_token {
    t_token_type type;
    char *value;
} t_token;

// Węzeł listy tokenów
typedef struct s_token_node {
    t_token token;
    struct s_token_node *next;
} t_token_node;

// Struktura drzewa
typedef struct s_tree_node {
    t_token token;
    struct s_tree_node *left;
    struct s_tree_node *right;
} t_tree_node;

// Struktura komendy
typedef struct s_cmd {
    char **argv;
    int argc;
    struct s_cmd *next;
} t_cmd;

// Struktura informacji
typedef struct s_info {
    int last_exit_status;
    t_cmd *table;
} t_info;

// Struktura promptu
typedef struct s_prompt {
    char *start_ptr_save;
} t_prompt;

// Prototypy funkcji
void init_prompt(t_prompt *prompt);
bool default_display_with_history(t_prompt *prompt, t_info *structure);
bool if_no_cmd_tokens(t_token_node *tokens);
bool open_redirection_files(t_token_node *tokens);
void free_token_list_full(t_token_node **tokens);
t_token_node *init_token_list(t_info *structure, t_prompt *prompt);
t_tree_node *init_binary_tree(t_token_node **tokens);

#endif