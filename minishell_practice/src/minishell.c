/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:33 by aneekhra          #+#    #+#             */
/*   Updated: 2024/05/23 12:09:30 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void display_prompt() {
    char *input;

    while (1) {
        // Display the prompt and read input
        input = readline("minishell> ");

        // If readline encounters EOF, it returns NULL
        if (!input) {
            printf("\n");
            break;
        }

        // If the input is not empty, add it to the history
        if (*input) {
            add_history(input);
        }

        // For now, just print the input
        printf("You entered: %s\n", input);

        // Free the allocated input
        free(input);
    }
}

int main(void) {
   // display_prompt();
    return 0;
}
