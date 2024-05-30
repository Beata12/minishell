/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/29 14:41:24 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int shell_cd(char **args)
{
    if (!args[1])
	{
        fprintf(stderr, "cd: missing argument\n");
        return 1;
    }
    if (chdir(args[1]) != 0)//changing diractory
	{
        perror("cd");
        return 1;
    }
    return (0);
}

// int main(int argc, char *argv[])
// {
//     int result = shell_cd(&argv[1]);

//     if (argc != 2)
// 	{
//         fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
//         exit(1);
//     }
//     if (result != 0) 
// 	{
//         fprintf(stderr, "Error: Failed to change directory\n");
//         exit(1);
//     }
//     printf("Directory changed successfully\n");
//     return (0);
// }