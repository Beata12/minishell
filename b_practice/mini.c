#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_OUT,
    TOKEN_REDIRECT_APPEND,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

void display_prompt(void)
{
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
    printf("@minishell:%s$ ", cwd);
    free(cwd);
}


//tokenization
Token *tokenize(char *command, int *token_count)
{
    Token *tokens = malloc(64 * sizeof(Token));
    int count = 0;
    char *token;
    const char *delimiters = " \t\n";

    token = strtok(command, delimiters);
    while (token != NULL)
    {
        TokenType type = TOKEN_UNKNOWN;

        if (strcmp(token, "|") == 0)
            type = TOKEN_PIPE;
        else if (strcmp(token, ">") == 0)
            type = TOKEN_REDIRECT_OUT;
        else if (strcmp(token, ">>") == 0)
            type = TOKEN_REDIRECT_APPEND;
        else
            type = TOKEN_WORD;

        tokens[count].type = type;
        tokens[count].value = strdup(token);
        count++;

        token = strtok(NULL, delimiters);
    }

    *token_count = count;
    return tokens;
}

//parsing
int parse_tokens(Token *tokens, int token_count)
{
    int i;

    for (i = 0; i < token_count; i++)
    {
        if (tokens[i].type == TOKEN_PIPE || tokens[i].type == TOKEN_REDIRECT_OUT || tokens[i].type == TOKEN_REDIRECT_APPEND)
        {
            // Check for syntax inconsistencies: no operator at start or end, no double operators
            if (i == 0 || i == token_count - 1 || tokens[i + 1].type == TOKEN_PIPE || tokens[i + 1].type == TOKEN_REDIRECT_OUT || tokens[i + 1].type == TOKEN_REDIRECT_APPEND)
            {
                fprintf(stderr, "Syntax error near '%s'\n", tokens[i].value);
                return 0;
            }
        }
    }

    return 1;
}

//execution
void execute_command(Token *tokens, int token_count)
{
    char *args[64];
    int arg_count = 0;
    pid_t pid;

    for (int i = 0; i < token_count; i++)
    {
        if (tokens[i].type == TOKEN_WORD)
        {
            args[arg_count++] = tokens[i].value;
        }
    }
    args[arg_count] = NULL;

    pid = fork();
    if (pid < 0)
    {
        perror("fork() error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execvp(args[0], args) < 0)
        {
            perror("execvp() error");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL);
    }
}

//main
int main(void)
{
    char *command;

    while (1)
    {
        display_prompt();
        command = readline(NULL);
        if (command == NULL)
            break;
        if (strlen(command) > 0)
        {
            add_history(command);

            int token_count;
            Token *tokens = tokenize(command, &token_count);

            if (parse_tokens(tokens, token_count))
            {
                execute_command(tokens, token_count);
            }

            for (int i = 0; i < token_count; i++)
            {
                free(tokens[i].value);
            }
            free(tokens);
        }
        free(command);
    }

    return 0;
}
