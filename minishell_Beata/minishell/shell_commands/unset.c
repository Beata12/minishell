/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:59 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/24 10:49:54 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/shell_commands.h"

int shell_unset(char **args)
{
    if (!args[1])
	{
        fprintf(stderr, "unset: missing argument\n");
        return 1;
    }
    if (unsetenv(args[1]) != 0)
	{
        perror("unset");
        return 1;
    }
    return (0);
}


int main()
{
    int status;
    char *args[] = {"unset", "my_variable", NULL};
    
	status = shell_unset(args);
    if (status != 0)
	{
        fprintf(stderr, "Error executing unset command\n");
        return 1;
    }
    printf("Unset command executed successfully\n");
    return 0;
}