/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:42:00 by aneekhra          #+#    #+#             */
/*   Updated: 2024/06/07 15:44:39 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "execution.h"
# include "minishell.h"

typedef enum e_token_types
{
	T_WORD,     // Word token
	T_RED_TO,   // Redirection to (>)
	T_RED_FROM, // Redirection from (<)
	T_DLESS,    // Here-document (<<)
	T_DGREAT,   // Append (>>)
	T_PIPE,     // Pipe (|)
	T_QUOTE,    // Quote (single or double)
	T_ERROR     // Error token
}			t_token_types;

// Structure for tokens
typedef struct
{
	char *value2;    // pointer for dynamic allocation
	char value[256]; // Value of the token, assuming max length 256 characters
	int		type;
}			Token;

typedef struct s_args
{
	int		pipes;
	int execution_result; // exit or no
	char	**cmds;
	char	**infiles;
	char	**outfiles;
	// t_list *env;

}			t_args;

void		handleWord(const char **ptr, Token *tokens, int *token_count);
void		handleQuote(const char **ptr, Token *tokens, int *token_count);
void		handlePipe(const char **ptr, Token *tokens, int *token_count);
void		handleSpecial(const char **ptr);
int			lex(const char *input, Token *tokens);
void		print_token_info(Token *tokens, int token_count);
// void		parser(char *input_command);

#endif

// // Prototypy funkcji
// void init_prompt(t_prompt *prompt);
// bool default_display_with_history(t_prompt *prompt, t_info *structure);
// bool if_no_cmd_tokens(t_token_node *tokens);
// bool open_redirection_files(t_token_node *tokens);
// void free_token_list_full(t_token_node **tokens);
// t_token_node *init_token_list(t_info *structure, t_prompt *prompt);
// t_tree_node *init_binary_tree(t_token_node **tokens);
