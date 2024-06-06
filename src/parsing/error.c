/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:41:15 by beata             #+#    #+#             */
/*   Updated: 2024/06/06 16:00:39 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum e_token_types
{
	T_WORD, // Word token
	T_RED_TO,   // Redirection to (>)
	T_RED_FROM, // Redirection from (<)
	T_DLESS,    // Here-document (<<)
	T_DGREAT,   // Append (>>)
	T_PIPE,     // Pipe (|)
	T_QUOTE,    // Quote (single or double)
	T_ERROR     // Error token
}       t_token_types;

// Structure for tokens
typedef struct
{
	char *value2;    // pointer for dynamic allocation
	char value[256]; // Value of the token, assuming max length 256 characters
	int	type;
}		Token;

typedef struct s_args
{
    int pipes;
    int execution_result; //exit or no
    char **cmds;
    char **infiles;
    char **outfiles;
    // t_list *env;
    
}       t_args;

#endif

int is_whitespace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int empty_input_flag(char *input_string)
{
    if (!input_string)
        return (1);
    while (*input_string && is_whitespace(*input_string))
        input_string++;
    if (*input_string)
        return (0);
    return (1);
}

void my_error(char *error_info, int error_code)
{
    printf("minishell: ");
    if (error_code == 2)
        printf("Syntax error: unexpected token near `%s'\n", error_info);
    if (error_code == 39)
        printf("Syntax error: unable to locate closing quotation");
    if (error_code == 0)
        printf("Warning: shell level (1000) too high, resetting to 1\n");
}

int unvalid_quotes(char *input_string)
{
    int i;
    int single_quote_flag;
    int double_quote_flag;

    i = 0;
    single_quote_flag = 0;
    double_quote_flag = 0;
    while (input_string[i])
    {
        if (input_string[i] == '\'' && !double_quote_flag)
            single_quote_flag = (single_quote_flag + 1) % 2;
        if (input_string[i] == '\"' && !single_quote_flag)
            double_quote_flag = (double_quote_flag + 1) % 2;
        i++;
    }
    if (single_quote_flag || double_quote_flag)
        return (1);
    return (0);
}

int track_quote_type(char input_string)
{}

void is_open_quote (char input_string, char *quote_flag)
{
    if ((track_quote_type(input_string)) && !*quote_flag)
        *quote_flag = input_string;
    else if ((track_quote_type(input_string)) && *quote_flag == input_string)
        *quote_flag = '\0';
}

int unvalid_symbols (char *input_string)
{
    char quote_status;

    quote_status = '\0';
    while (*input_string)
    {
        is_open_quote(*input_string, &quote_status);
        if ((*input_string == '&' || *input_string == ';' || *input_string == '\\') && !quote_status)
            return (*input_string);
        input_string++;
    }
    return (0);
}

int wrong_input(t_args *shell_data, char *input)
{
    int quote_error_flag;
    int symbol_error_flag;

    quote_error_flag = 0;
    symbol_error_flag = 0;
    quote_error_flag = unvalid_quotes(input);
    symbol_error_flag = unvalid_symbols(input);
    if (quote_error_flag || symbol_error_flag)
    {
        shell_data->execution_result = 2;
        if (quote_error_flag)
            my_error((char *)&quote_error_flag, 39);
        else if (symbol_error_flag)
            my_error((char *)&symbol_error_flag, shell_data->execution_result);
    }
    else if (empty_input_flag(input))
        shell_data->execution_result = 0;
    else
        return (0);
    return (1);
}

int main(int argc, char **argv)
{
    t_args shell_data; // Deklaracja zmiennej shell_data typu t_args

    if (argc > 1)
    {
        if (wrong_input(&shell_data, argv[1]))
        {
            printf("Podano nieprawidłowy argument.\n");
            return 1;
        }
        else
        {
            printf("Argument został przetworzony poprawnie.\n");
        }
    }
    else
    {
        printf("Brak argumentu. Użycie: %s <argument>\n", argv[0]); 
        return 1;
    }
    return 0;
}
