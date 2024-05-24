/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:45 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/24 12:35:46 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_files/shell_commands.h"

int shell_export(char *arg)
{
    char *equals = strchr(arg, '=');

    if (!equals)
	{
        fprintf(stderr, "Invalid argument format: %s\n", arg);
        return 1;
    }
    *equals = '\0';  // Splitting the argument into variable name and value
    int result = setenv(arg, equals + 1, 1); // Setting the environment variable
    if (result != 0)
	{
        perror("setenv");
        return 1;
    }
    return 0;
}

// int main(int argc, char *argv[])
// {
//     int result = shell_export(argv[1]);

//     if (argc != 2)
// 	{
//         fprintf(stderr, "Usage: %s <variable=value>\n", argv[0]);
//         return 1;
//     }
//     if (result != 0)
// 	{
//         fprintf(stderr, "Error: Failed to export variable\n");
//         return 1;
//     }
//     printf("Variable exported successfully\n");
//     return 0;
// }

//	check like this:
//	./a.out MY_VAR=my_value

// int shell_export(char **args) {
//     if (!args[1])
// 	{
//         fprintf(stderr, "export: missing argument\n");
//         return 1;
//     }
//     if (putenv(args[1]) != 0)
// 	{
//         perror("export");
//         return 1;
//     }
//     return 0;
// }

// int main(int argc, char *argv[]) 
// {
//     int result = shell_export(&argv[1]);

//     if (argc != 2) {
//         fprintf(stderr, "Usage: %s <variable=value>\n", argv[0]);
//         exit(1);
//     }
//     if (result != 0) {
//         fprintf(stderr, "Error: Failed to export variable\n");
//         exit(1);
//     }
//     printf("Variable exported successfully\n");
//     return 0;
// }