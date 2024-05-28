/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:42 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/27 17:04:22 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int shell_exit()
{
    // Free memory allocated for each argument
	printf("\n");
    // Terminate the program
    exit(EXIT_SUCCESS);
}

// int main()
// {
//     shell_exit();
//         printf("This line will never be reached\n");
//     return (0);
// }