/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:45 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/31 12:22:37 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char **environ;

void shell_export(char *args)
{
    if (args[1] == NULL) {
        // No argument, print all environment variables
        for (char **env = environ; *env != 0; env++) {
            printf("%s\n", *env);
        }
    } else {
        // Parse the argument
        char *name = strtok(args[1], "=");
        char *value = strtok(NULL, "=");

        if (name && value) {
            // Find if the variable already exists
            int index = find_env_var(name);
            if (index != -1) {
                // Replace existing value
                size_t len = strlen(name) + strlen(value) + 2;
                char *new_env_var = malloc(len);
                snprintf(new_env_var, len, "%s=%s", name, value);
                environ[index] = new_env_var;
            } else {
                // Add new environment variable
                size_t len = strlen(name) + strlen(value) + 2;
                char *new_env_var = malloc(len);
                snprintf(new_env_var, len, "%s=%s", name, value);

                // Count current environment variables
                int env_count = 0;
                while (environ[env_count] != NULL) {
                    env_count++;
                }

                // Allocate space for the new environment variable
                environ = realloc(environ, (env_count + 2) * sizeof(char *));
                environ[env_count] = new_env_var;
                environ[env_count + 1] = NULL;
            }
        } else {
            fprintf(stderr, "minishell: export: invalid format\n");
        }
    }
}



// {
//     char *equals = strchr(arg, '=');

//     if (!equals)
// 	{
//         fprintf(stderr, "Invalid argument format: %s\n", arg);
//         return 1;
//     }
//     *equals = '\0';  // Splitting the argument into variable name and value
//     int result = setenv(arg, equals + 1, 1); // Setting the environment variable
//     if (result != 0)
// 	{
//         perror("setenv");
//         return 1;
//     }
//     return 0;
// }

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