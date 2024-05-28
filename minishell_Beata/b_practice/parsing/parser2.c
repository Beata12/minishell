#include <stdio.h>
#include <stdlib.h> // Nagłówek dla malloc, free
#include <string.h>

// Enum definitions for token types
typedef enum e_token_types {
	T_WORD = 0,
	T_RED_TO,
	T_RED_FROM,
	T_DLESS,
	T_DGREAT,
	T_PIPE
} t_token_types;

// Enum definitions for actions
typedef enum e_actions {
	SHIFT,
	REDUCE,
	ACCEPT
} t_actions;

// Structure for tokens
typedef struct {
	int type;
	char value[256]; // Assuming a maximum token length of 256 characters
} Token;

// Structure for the parsing table
typedef struct {
	int state;
	int token_type;
	int action;
	int next_state;
	int reduced_tokens;
} ParsingTableEntry;

ParsingTableEntry parsing_table[] = {
	{0, T_WORD, SHIFT, 1, -1},
	{0, T_RED_TO, SHIFT, 2, -1},
	{0, T_RED_FROM, SHIFT, 3, -1},
	{0, T_PIPE, SHIFT, 4, -1},
	{1, T_WORD, REDUCE, 0, 1},
	{1, T_RED_TO, SHIFT, 2, -1},
	{1, T_RED_FROM, SHIFT, 3, -1},
	{1, T_PIPE, SHIFT, 4, -1},
	{2, T_WORD, SHIFT, 5, -1},
	{3, T_WORD, SHIFT, 6, -1},
	{4, T_WORD, SHIFT, 1, -1},
	{4, T_RED_TO, SHIFT, 2, -1},
	{4, T_RED_FROM, SHIFT, 3, -1},
	{4, T_PIPE, SHIFT, 4, -1},
	{5, T_WORD, REDUCE, 1, 3}, // Example reduction after a redirection target
	{5, T_PIPE, REDUCE, 1, 3},
	{6, T_WORD, REDUCE, 1, 3}, // Example reduction after a redirection source
	{6, T_PIPE, REDUCE, 1, 3},
	{1, -1, ACCEPT, -1, -1} // Accept state
};

void parse_tokens(Token *tokens, int token_count)
{
    int state = 0;
    int *stack = malloc(1024 * sizeof(int)); // dynamiczna alokacja pamięci dla stosu
    int stack_pointer = 0;
    int i = 0;
    
	if (stack == NULL)
	{
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }
    stack[stack_pointer++] = state;
    while (i < token_count)
	{
        size_t j = 0;
        Token token = tokens[i];
        int action = -1;
        int next_state = -1;
        int reduced_tokens = -1;

        // Find the appropriate action in the parsing table
        while (j < sizeof(parsing_table) / sizeof(ParsingTableEntry))
		{
            if (parsing_table[j].state == state && parsing_table[j].token_type == token.type)
			{
                action = parsing_table[j].action;
                next_state = parsing_table[j].next_state;
                reduced_tokens = parsing_table[j].reduced_tokens;
                break;
            }
            j++;
        }
        // Perform the appropriate action (SHIFT, REDUCE, ACCEPT)
        if (action == SHIFT)
		{
            state = next_state;
            stack[stack_pointer++] = state;
            i++;
        }
		else if (action == REDUCE)
		{
            // Remove reduced tokens from the stack
            stack_pointer -= reduced_tokens;
            state = stack[stack_pointer - 1];
            // Change state based on reduction
            stack[stack_pointer++] = next_state;
        }
		else if (action == ACCEPT)
		{
            printf("Parsing completed successfully.\n");
            free(stack);
            return;
        }
		else
		{
            printf("Syntax error.\n");
            free(stack);
            return;
        }
    }
    free(stack);
}

// Simple lexical function (lexer) to tokenize the input
int lex(const char *input, Token *tokens) {
	int token_count = 0;
	char *input_copy = strdup(input); // Copy input to avoid modifying the original
	char *token = strtok(input_copy, " ");

	while (token != NULL)
	{
		tokens[token_count].type = T_WORD; // Assuming all tokens are of type T_WORD for simplicity
		strncpy(tokens[token_count].value, token, sizeof(tokens[token_count].value) - 1);
		tokens[token_count].value[sizeof(tokens[token_count].value) - 1] = '\0';
		token_count++;
		token = strtok(NULL, " ");
	}
	free(input_copy); // Free memory allocated by strdup
	return token_count;
}

void parser(char *input_command) {
	Token tokens[1024];
	int token_count = lex(input_command, tokens);
	int i = 1;

	if (token_count > 0 && strcmp(tokens[0].value, "echo") == 0)
	{
		printf("Echoing:");
		while (i < token_count)
		{
			printf(" %s", tokens[i].value);
			i++;
		}
		printf("\n");
	}
	else
		printf("Unknown command: %s\n", tokens[0].value);
}

int main(int argc, char **argv)
{
	size_t length = 0;
	int i = 1;
	char *command = malloc(length);

	if (argc < 2)
	{
		printf("Usage: %s <command>\n", argv[0]);
		return 1;
	}
	// Concatenate all arguments into one command
	while (i < argc)
	{
		length += strlen(argv[i]) + 1;
		i++;
	}
	if (!command)
	{
		perror("malloc");
		return 1;
	}
	command[0] = '\0';
	i = 1;
	while (i < argc)
	{
		strcat(command, argv[i]);
		if (i < argc - 1)
		{
			strcat(command, " ");
		}
		i++;
	}
	parser(command);
	free(command);
	return 0;
}

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
