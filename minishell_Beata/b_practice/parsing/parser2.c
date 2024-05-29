#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definicje enum dla typów tokenów
typedef enum e_token_types {
    T_WORD = 0,
    T_RED_TO,
    T_RED_FROM,
    T_DLESS,
    T_DGREAT,
    T_PIPE,
    T_QUOTE,
    T_ERROR
} t_token_types;

// Struktura dla tokenów
typedef struct {
    int type;
    char value[256]; // Zakładamy maksymalną długość tokena 256 znaków
} Token;

// Prosta funkcja leksykalna (lexer) do tokenizacji wejścia
int lex(const char *input, Token *tokens) {
    int token_count = 0;
    const char *ptr = input;

    while (*ptr != '\0') {
        // Pomijanie białych znaków
        while (isspace(*ptr)) {
            printf("Whitespace found, skipping...\n");
            ptr++;
        }

        if (*ptr == '\0') break;

        if (*ptr == '|') {
            // Obsługa znaku pipe
            printf("Pipe found, adding token...\n");
            tokens[token_count].type = T_PIPE;
            tokens[token_count].value[0] = *ptr;
            tokens[token_count].value[1] = '\0';
            ptr++;
        } else if (*ptr == '"') {
            // Obsługa cudzysłowów
            printf("Quote found, adding token...\n");
            tokens[token_count].type = T_QUOTE;
            int len = 0;
            ptr++; // Pomijamy początkowy cudzysłów
            while (*ptr != '\0' && *ptr != '"' && len < 255) {
                printf("Processing character: %c\n", *ptr);
                tokens[token_count].value[len++] = *ptr++;
            }
            if (*ptr == '"') {
                printf("End quote found, adding token...\n");
                ptr++; // Pomijamy końcowy cudzysłów
            }
            tokens[token_count].value[len] = '\0';
        } else {
            // Obsługa słów
            printf("Word found, adding token...\n");
            int len = 0;
            while (*ptr != '\0' && !isspace(*ptr) && *ptr != '|' && *ptr != '"' && len < 255) {
                printf("Processing character: %c\n", *ptr);
                tokens[token_count].value[len++] = *ptr++;
            }
            tokens[token_count].value[len] = '\0';
            tokens[token_count].type = T_WORD;
        }
        token_count++;
    }
    return token_count;
}

void print_token_info(Token *tokens, int token_count) {
    for (int i = 0; i < token_count; i++) {
        printf("Token %d: typ: ", i + 1);
        switch (tokens[i].type) {
            case T_WORD: printf("WORD"); break;
            case T_RED_TO: printf("RED_TO"); break;
            case T_RED_FROM: printf("RED_FROM"); break;
            case T_DLESS: printf("DLESS"); break;
            case T_DGREAT: printf("DGREAT"); break;
            case T_QUOTE: printf("QUOTE"); break;
            case T_PIPE: printf("PIPE"); break;
            default: printf("ERROR"); break;
        }
        printf(", wartość: %s\n", tokens[i].value);
    }
}

void parser(char *input_command) {
    Token tokens[1024];
    int token_count = lex(input_command, tokens);

    print_token_info(tokens, token_count); // Drukowanie informacji o tokenach

    if (token_count > 0 && strcmp(tokens[0].value, "echo") == 0) {
        printf("Echoing:");
        for (int i = 1; i < token_count; i++) {
            printf(" %s", tokens[i].value);
        }
        printf("\n");
    } else {
        // Można dodać logikę parsowania poleceń innych niż echo
        printf("Other command parsing is not implemented yet.\n");
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <command>\n", argv[0]);
        return 1;
    }

    size_t length = 0;
    for (int i = 1; i < argc; i++) {
        length += strlen(argv[i]) + 1;
    }

    char *command = malloc(length);
    if (!command) {
        perror("malloc");
        return 1;
    }

    command[0] = '\0';
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        if (i < argc - 1) {
            strcat(command, " ");
        }
    }

    parser(command);
    free(command);
    return 0;
}
// #include <stdio.h>
// #include <stdlib.h> // Nagłówek dla malloc, free
// #include <string.h>
// #include <ctype.h> // Nagłówek dla isspace

// // Definicje enum dla typów tokenów
// typedef enum e_token_types {
//     T_WORD = 0,
//     T_RED_TO,
//     T_RED_FROM,
//     T_DLESS,
//     T_DGREAT,
//     T_PIPE,
//     T_QUOTE,
//     T_ERROR
// } t_token_types;

// // Definicje enum dla akcji
// typedef enum e_actions {
//     SHIFT,
//     REDUCE,
//     ACCEPT
// } t_actions;

// // Struktura dla tokenów
// typedef struct {
//     int type;
//     char value[256]; // Zakładamy maksymalną długość tokena 256 znaków
// } Token;

// // Struktura dla tabeli parsowania
// typedef struct {
//     int state;
//     int token_type;
//     int action;
//     int next_state;
//     int reduced_tokens;
// } ParsingTableEntry;

// ParsingTableEntry parsing_table[] = {
//     {0, T_WORD, SHIFT, 1, -1},
//     {0, T_RED_TO, SHIFT, 2, -1},
//     {0, T_RED_FROM, SHIFT, 3, -1},
//     {0, T_PIPE, SHIFT, 4, -1},
//     {1, T_WORD, REDUCE, 0, 1},
//     {1, T_RED_TO, SHIFT, 2, -1},
//     {1, T_RED_FROM, SHIFT, 3, -1},
//     {1, T_PIPE, SHIFT, 4, -1},
//     {2, T_WORD, SHIFT, 5, -1},
//     {3, T_WORD, SHIFT, 6, -1},
//     {4, T_WORD, SHIFT, 1, -1},
//     {4, T_RED_TO, SHIFT, 2, -1},
//     {4, T_RED_FROM, SHIFT, 3, -1},
//     {4, T_PIPE, SHIFT, 4, -1},
//     {5, T_WORD, REDUCE, 1, 3}, // Przykład redukcji po celu przekierowania
//     {5, T_PIPE, REDUCE, 1, 3},
//     {6, T_WORD, REDUCE, 1, 3}, // Przykład redukcji po źródle przekierowania
//     {6, T_PIPE, REDUCE, 1, 3},
//     {1, -1, ACCEPT, -1, -1} // Stan akceptacji
// };

// void parse_tokens(Token *tokens, int token_count)
// {
//     int state = 0;
//     int *stack = malloc(1024 * sizeof(int)); // dynamiczna alokacja pamięci dla stosu
//     int stack_pointer = 0;
//     int i = 0;

//     if (stack == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed.\n");
//         return;
//     }
//     stack[stack_pointer++] = state;
//     while (i < token_count)
//     {
//         size_t j = 0;
//         Token token = tokens[i];
//         int action = -1;
//         int next_state = -1;
//         int reduced_tokens = -1;

//         // Znajdź odpowiednią akcję w tabeli parsowania
//         while (j < sizeof(parsing_table) / sizeof(ParsingTableEntry))
//         {
//             if (parsing_table[j].state == state && parsing_table[j].token_type == token.type)
//             {
//                 action = parsing_table[j].action;
//                 next_state = parsing_table[j].next_state;
//                 reduced_tokens = parsing_table[j].reduced_tokens;
//                 break;
//             }
//             j++;
//         }
//         // Wykonaj odpowiednią akcję (SHIFT, REDUCE, ACCEPT)
//         if (action == SHIFT)
//         {
//             state = next_state;
//             stack[stack_pointer++] = state;
//             i++;
//         }
//         else if (action == REDUCE)
//         {
//             // Usuń zredukowane tokeny ze stosu
//             stack_pointer -= reduced_tokens;
//             state = stack[stack_pointer - 1];
//             // Zmień stan na podstawie redukcji
//             stack[stack_pointer++] = next_state;
//         }
//         else if (action == ACCEPT)
//         {
//             printf("Parsing completed successfully.\n");
//             free(stack);
//             return;
//         }
//         else
//         {
//             printf("Syntax error.\n");
//             free(stack);
//             return;
//         }
//     }
//     free(stack);
// }

// int is_special_char(char c) {
//     return c == '|' || c == '>' || c == '<';
// }

// // Prosta funkcja leksykalna (lexer) do tokenizacji wejścia
// int lex(const char *input, Token *tokens) {
//     int token_count = 0;
//     const char *ptr = input;

//     while (*ptr != '\0')
//     {
//         // Pomijanie białych znaków
//         while (isspace(*ptr)) {
//             ptr++;
//         }

//         if (*ptr == '\0') break;

//         if (is_special_char(*ptr)) {
//             // Obsługa znaków specjalnych
//             tokens[token_count].type = (*ptr == '|') ? T_PIPE : 
//                                        (*ptr == '>') ? T_RED_TO : T_RED_FROM;
//             if (*ptr == '>' && *(ptr + 1) == '>') {
//                 tokens[token_count].type = T_DGREAT;
//                 ptr++;
//             }
//             if (*ptr == '<' && *(ptr + 1) == '<') {
//                 tokens[token_count].type = T_DLESS;
//                 ptr++;
//             }
//             tokens[token_count].value[0] = *ptr;
//             tokens[token_count].value[1] = '\0';
//             ptr++;
//         } else if (*ptr == '"') {
//             // Obsługa cudzysłowów
//             tokens[token_count].type = T_QUOTE;
//             tokens[token_count].value[0] = *ptr;
//             tokens[token_count].value[1] = '\0';
//             ptr++;
//         } else {
//             // Obsługa słów
//             int len = 0;
//             while (*ptr != '\0' && !isspace(*ptr) && !is_special_char(*ptr) && len < 255) {
//                 tokens[token_count].value[len++] = *ptr++;
//             }
//             tokens[token_count].value[len] = '\0';
//             tokens[token_count].type = T_WORD;
//         }
//         token_count++;
//     }
//     return token_count;
// }

// void print_token_info(Token *tokens, int token_count) {
//     for (int i = 0; i < token_count; i++) {
//         printf("Token %d: typ: ", i + 1);
//         switch (tokens[i].type) {
//             case T_WORD: printf("WORD"); break;
//             case T_RED_TO: printf("RED_TO"); break;
//             case T_RED_FROM: printf("RED_FROM"); break;
//             case T_DLESS: printf("DLESS"); break;
//             case T_DGREAT: printf("DGREAT"); break;
//             case T_PIPE: printf("PIPE"); break;
//             case T_QUOTE: printf("QUOTE"); break;
//             default: printf("ERROR"); break;
//         }
//         printf(", wartość: %s\n", tokens[i].value);
//     }
// }

// void parser(char *input_command) {
//     Token tokens[1024];
//     int token_count = lex(input_command, tokens);
    
//     print_token_info(tokens, token_count); // Drukowanie informacji o tokenach

//     if (token_count > 0 && strcmp(tokens[0].value, "echo") == 0)
//     {
//         printf("Echoing:");
//         for (int i = 1; i < token_count; i++)
//         {
//             printf(" %s", tokens[i].value);
//         }
//         printf("\n");
//     }
//     else
//     {
//         parse_tokens(tokens, token_count);
//     }
// }

// int main(int argc, char **argv)
// {
//     if (argc < 2)
//     {
//         printf("Usage: %s <command>\n", argv[0]);
//         return 1;
//     }

//     size_t length = 0;
//     for (int i = 1; i < argc; i++)
//     {
//         length += strlen(argv[i]) + 1;
//     }

//     char *command = malloc(length);
//     if (!command)
//     {
//         perror("malloc");
//         return 1;
//     }

//     command[0] = '\0';
//     for (int i = 1; i < argc; i++)
//     {
//         strcat(command, argv[i]);
//         if (i < argc - 1)
//         {
//             strcat(command, " ");
//         }
//     }

//     parser(command);
//     free(command);
//     return 0;
// }

// int main(int argc, char **argv)
// {
//	 if (argc < 2)
//	 {
//		 printf("Usage: %s <command>\n", argv[0]);
//		 return 1; 
//	 }

//	 // Join all arguments into a single command string
//	 char command[1024] = {0};
//	 for (int i = 1; i < argc; i++)
//	 {
//		 strcat(command, argv[i]);
//		 if (i < argc - 1)
//		 {
//			 strcat(command, " ");
//		 }
//	 }

//	 parser(command);
//	 return 0;
// }
