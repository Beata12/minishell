/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 07:42:37 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/28 11:50:20 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_tree_node *create_tree_node(t_token_node *token_node) {
    t_tree_node *node = (t_tree_node *)malloc(sizeof(t_tree_node));
    if (!node)
        return NULL;

    node->token = token_node->token;
    node->left = NULL;
    node->right = NULL;
    return node;
}

t_tree_node *build_tree(t_token_node **tokens) {
    if (!(*tokens) || (*tokens)->token.type == TOKEN_END)
        return NULL;

    t_tree_node *node = create_tree_node(*tokens);
    *tokens = (*tokens)->next;

    if (node->token.type == TOKEN_PIPE) {
        node->left = build_tree(tokens);
        node->right = build_tree(tokens);
    }

    return node;
}

t_tree_node *init_binary_tree(t_token_node **tokens) {
    return build_tree(tokens);
}

void add_command(t_cmd **head, char **argv, int argc) {
    t_cmd *new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
    new_cmd->argv = argv;
    new_cmd->argc = argc;
    new_cmd->next = NULL;

    if (*head == NULL) {
        *head = new_cmd;
    } else {
        t_cmd *current = *head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_cmd;
    }
}

void free_tree(t_tree_node *tree) {
    if (!tree)
        return;

    free_tree(tree->left);
    free_tree(tree->right);
    free(tree->token.value);
    free(tree);
}

void init_prompt(t_prompt *prompt)
{
	(void)prompt;
    char *cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	printf("@minishell:%s$ ", cwd);
	free(cwd);
}

bool default_display_with_history(t_prompt *prompt, t_info *structure) {
	(void)prompt;
	(void)structure;
    return true;
}

bool if_no_cmd_tokens(t_token_node *tokens) {
	(void)tokens;
    return false;
}

bool open_redirection_files(t_token_node *tokens) {
	(void)tokens;
    return true;
}

void free_token_list_full(t_token_node **tokens) {
    t_token_node *current = *tokens;
    t_token_node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current->token.value);
        free(current);
        current = next;
    }
    
    *tokens = NULL;
}

t_token_node *create_token(t_token_type type, const char *value) {
    t_token_node *new_token = (t_token_node *)malloc(sizeof(t_token_node));
    if (!new_token)
        return NULL;

    new_token->token.type = type;
    new_token->token.value = strdup(value);
    new_token->next = NULL;

    return new_token;
}

void add_token(t_token_node **tokens, t_token_node *new_token) {
    t_token_node *current = *tokens;
    if (!current) {
        *tokens = new_token;
    } else {
        while (current->next)
            current = current->next;
        current->next = new_token;
    }
}

t_token_node *init_token_list(t_info *structure, t_prompt *prompt) {
	(void)structure;
    if (!prompt || !prompt->start_ptr_save) {
        // Handle the case where prompt or start_ptr_save is NULL
        return NULL;
    }

    char *input = prompt->start_ptr_save;
    t_token_node *tokens = NULL;
    char buffer[256];
    int buffer_index = 0;

    while (*input) {
        if (isspace(*input)) {
            input++;
            continue;
        }

        if (*input == '|') {
            add_token(&tokens, create_token(TOKEN_PIPE, "|"));
            input++;
            continue;
        }

        if (*input == '>') {
            add_token(&tokens, create_token(TOKEN_REDIRECTION_OUT, ">"));
            input++;
            continue;
        }

        if (*input == '<') {
            add_token(&tokens, create_token(TOKEN_REDIRECTION_IN, "<"));
            input++;
            continue;
        }

        buffer_index = 0;
        while (*input && !isspace(*input) && *input != '|' && *input != '>' && *input != '<') {
            buffer[buffer_index++] = *input++;
        }
        buffer[buffer_index] = '\0';
        add_token(&tokens, create_token(TOKEN_WORD, buffer));
    }

    add_token(&tokens, create_token(TOKEN_END, ""));
    return tokens;
}

void traverse_tree(t_tree_node *tree, t_cmd **cmd_table) {
    if (!tree)
        return;

    if (tree->token.type == TOKEN_WORD) {
        char **argv = (char **)malloc(sizeof(char *) * 2);
        argv[0] = strdup(tree->token.value);
        argv[1] = NULL;
        add_command(cmd_table, argv, 1);
    }

    traverse_tree(tree->left, cmd_table);
    traverse_tree(tree->right, cmd_table);
}

void init_cmd_table(t_tree_node *tree, t_cmd **table, t_cmd **head, t_prompt *prompt) {
	(void)prompt;
    traverse_tree(tree, head);
    *table = *head;
}

bool parser(t_info *structure, t_prompt *prompt) {
    t_token_node *tokens;

    init_prompt(prompt);
    if (!default_display_with_history(prompt, structure))
        return false;
    tokens = init_token_list(structure, prompt); // Tokenizacja
    if (!tokens || if_no_cmd_tokens(tokens)) {
        if (if_no_cmd_tokens(tokens)) {
            if (!open_redirection_files(tokens))
                structure->last_exit_status = 1;
        }
        free_token_list_full(&tokens);
        free(prompt->start_ptr_save);
        return false;
    }
    t_tree_node *tree = init_binary_tree(&tokens); // Budowanie drzewa binarnego
    structure->table = NULL;
    t_cmd *head = NULL;
    init_cmd_table(tree, &structure->table, &head, prompt); // Inicjalizacja tabeli komend
    free_tree(tree); // Zwolnienie drzewa binarnego
    if (!structure->table) {
        free(prompt->start_ptr_save);
        return false;
    }
    free(prompt->start_ptr_save);
    return true;
}

int main() {
    t_info structure;
    t_prompt prompt;

    structure.last_exit_status = 0;
    if (parser(&structure, &prompt))
        printf("Pomyślnie sparsowano polecenie!\n");
    else
	{
        structure.last_exit_status = 1;
        printf("Błąd podczas parsowania polecenia!\n");
    }
    return 0;
}

// t_token_node *init_token_list(t_info *structure, t_prompt *prompt) {
//     char *input = prompt->start_ptr_save; // Zakładam, że to trzyma wejściowy ciąg znaków
//     t_token_node *tokens = NULL;
//     char buffer[256];
//     int buffer_index = 0;

//     while (*input) {
//         if (isspace(*input)) {
//             input++;
//             continue;
//         }

//         if (*input == '|') {
//             add_token(&tokens, create_token(TOKEN_PIPE, "|"));
//             input++;
//             continue;
//         }

//         if (*input == '>') {
//             add_token(&tokens, create_token(TOKEN_REDIRECTION_OUT, ">"));
//             input++;
//             continue;
//         }

//         if (*input == '<') {
//             add_token(&tokens, create_token(TOKEN_REDIRECTION_IN, "<"));
//             input++;
//             continue;
//         }

//         buffer_index = 0;
//         while (*input && !isspace(*input) && *input != '|' && *input != '>' && *input != '<') {
//             buffer[buffer_index++] = *input++;
//         }
//         buffer[buffer_index] = '\0';
//         add_token(&tokens, create_token(TOKEN_WORD, buffer));
//     }

//     add_token(&tokens, create_token(TOKEN_END, ""));
//     return tokens;
// }

// t_token_node *init_token_list(t_info *structure, t_prompt *prompt) {
//     char *input = prompt->start_ptr_save; // Zakładam, że to trzyma wejściowy ciąg znaków
//     t_token_node *tokens = NULL;
//     char buffer[256];
//     int buffer_index = 0;

//     while (*input) {
//         if (isspace(*input)) {
//             input++;
//             continue;
//         }

//         if (*input == '|') {
//             add_token(&tokens, create_token(TOKEN_PIPE, "|"));
//             input++;
//             continue;
//         }

//         if (*input == '>') {
//             add_token(&tokens, create_token(TOKEN_REDIRECTION_OUT, ">"));
//             input++;
//             continue;
//         }

//         if (*input == '<') {
//             add_token(&tokens, create_token(TOKEN_REDIRECTION_IN, "<"));
//             input++;
//             continue;
//         }

//         buffer_index = 0;
//         while (*input && !isspace(*input) && *input != '|' && *input != '>' && *input != '<') {
//             buffer[buffer_index++] = *input++;
//         }
//         buffer[buffer_index] = '\0';
//         add_token(&tokens, create_token(TOKEN_WORD, buffer));
//     }

//     add_token(&tokens, create_token(TOKEN_END, ""));
//     return tokens;
// }

// bool parser(t_info *structure, t_prompt *prompt) {
//     t_token_node *tokens;

//     init_prompt(prompt);
//     if (!default_display_with_history(prompt, structure))
//         return false;
//     tokens = init_token_list(structure, prompt); // Tokenizacja
//     if (!tokens || if_no_cmd_tokens(tokens)) {
//         if (if_no_cmd_tokens(tokens)) {
//             if (!open_redirection_files(tokens))
//                 structure->last_exit_status = 1;
//         }
//         free_token_list_full(&tokens);
//         free(prompt->start_ptr_save);
//         return false;
//     }
//     structure->table = parse(tokens, prompt); // Parsowanie
//     if (!structure->table) {
//         free(prompt->start_ptr_save);
//         return false;
//     }
//     free(prompt->start_ptr_save);
//     return true;
// }

// t_token_node *init_binary_tree(t_token_node **tokens) {
//     // Implementacja tworzenia drzewa binarnego z tokenów
//     // To może być zaawansowana funkcja w zależności od struktury tokenów
//     return *tokens;
// }

// void init_cmd_table(t_token_node *tree, t_cmd **table, t_cmd **head, t_prompt *prompt) {
//     // Implementacja inicjalizacji tabeli komend na podstawie drzewa
//     // Przykładowa implementacja w zależności od struktury drzewa i komend
// }

// void free_tree(t_token_node *tree) {
//     // Implementacja zwalniania pamięci zajmowanej przez drzewo binarne
// }

// // Funkcje pomocnicze
// void init_prompt(t_prompt *prompt) {
//     // Inicjalizacja promptu
// }

// bool default_display_with_history(t_prompt *prompt, t_info *structure) {
//     // Wyświetlanie promptu z historią
//     return true;
// }

// bool if_no_cmd_tokens(t_token_node *tokens) {
//     // Sprawdzenie, czy nie ma tokenów komend
//     return false;
// }

// bool open_redirection_files(t_token_node *tokens) {
//     // Otwarcie plików redirection, jeśli istnieją
//     return true;
// }

// void free_token_list_full(t_token_node **tokens) {
//     // Zwolnienie pamięci zajmowanej przez listę tokenów
//     t_token_node *current = *tokens;
//     t_token_node *next;
    
//     while (current != NULL) {
//         next = current->next;
//         free(current->token.value);
//         free(current);
//         current = next;
//     }
    
//     *tokens = NULL;
// }

// t_token_node *create_token(t_token_type type, const char *value) {
//     t_token_node *new_token = (t_token_node *)malloc(sizeof(t_token_node));
//     if (!new_token)
//         return NULL;

//     new_token->token.type = type;
//     new_token->token.value = strdup(value);
//     new_token->next = NULL;

//     return new_token;
// }

// void add_token(t_token_node **tokens, t_token_node *new_token) {
//     t_token_node *current = *tokens;
//     if (!current) {
//         *tokens = new_token;
//     } else {
//         while (current->next)
//             current = current->next;
//         current->next = new_token;
//     }
// }

// t_token_node *init_token_list(t_info *structure, t_prompt *prompt) {
//     char *input = prompt->start_ptr_save;
//     t_token_node *tokens = NULL;
//     char buffer[256];
//     int buffer_index = 0;

//     while (*input) {
//         if (isspace(*input)) {
//             input++;
//             continue;
//         }

//         if (*input == '|') {
//             add_token(&tokens, create_token(TOKEN_PIPE, "|"));
//             input++;
//             continue;
//         }

//         if (*input == '>') {
//             add_token(&tokens, create_token(TOKEN_REDIRECTION_OUT, ">"));
//             input++;
//             continue;
//         }

//         if (*input == '<') {
//             add_token(&tokens, create_token(TOKEN_REDIRECTION_IN, "<"));
//             input++;
//             continue;
//         }

//         buffer_index = 0;
//         while (*input && !isspace(*input) && *input != '|' && *input != '>' && *input != '<') {
//             buffer[buffer_index++] = *input++;
//         }
//         buffer[buffer_index] = '\0';
//         add_token(&tokens, create_token(TOKEN_WORD, buffer));
//     }

//     add_token(&tokens, create_token(TOKEN_END, ""));
//     return tokens;
// }

// t_cmd *parse(t_token_node *tokens, t_prompt *prompt) {
//     t_token_node *tree;
//     t_cmd *table;
//     t_cmd *head;

//     tree = init_binary_tree(&tokens);
//     table = NULL;
//     head = NULL;
//     init_cmd_table(tree, &table, &head, prompt);
//     free_tree(tree);
//     return head;
// }

// t_token_node *init_binary_tree(t_token_node **tokens) {
//     return *tokens;  // Implementacja tworzenia drzewa binarnego
// }

// void init_cmd_table(t_token_node *tree, t_cmd **table, t_cmd **head, t_prompt *prompt) {
//     // Implementacja inicjalizacji tabeli komend
// }

// void free_tree(t_token_node *tree) {
//     // Zwolnienie pamięci zajmowanej przez drzewo
// }

// bool parser(t_info *structure, t_prompt *prompt) {
//     t_token_node *tokens;

//     init_prompt(prompt);
//     if (!default_display_with_history(prompt, structure))
//         return false;
//     tokens = init_token_list(structure, prompt); // Tokenizacja
//     if (!tokens || if_no_cmd_tokens(tokens)) {
//         if (if_no_cmd_tokens(tokens)) {
//             if (!open_redirection_files(tokens))
//                 structure->last_exit_status = 1;
//         }
//         free_token_list_full(&tokens);
//         free(prompt->start_ptr_save);
//         return false;
//     }
//     structure->table = parse(tokens, prompt); // Parsowanie
//     if (!structure->table) {
//         free(prompt->start_ptr_save);
//         return false;
//     }
//     free(prompt->start_ptr_save);
//     return true;
// }
