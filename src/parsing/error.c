/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beata <beata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:41:15 by beata             #+#    #+#             */
/*   Updated: 2024/06/06 15:25:18 by beata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// int unvalid_symbols (char *input_string)
// {
//     char quote_status;

//     quote_status = '\0';
//     while (*input_string)
//     {
        
//     }
// }

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