/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:42 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/26 13:26:56 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int shell_exit()
{
    // Free memory allocated for each argument
	printf("\n");
    // Terminate the program
    exit(0);
}

// int main()
// {
//     shell_exit();
//         printf("This line will never be reached\n");
//     return (0);
// }