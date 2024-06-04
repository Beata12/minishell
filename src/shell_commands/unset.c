/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:58:59 by bmarek            #+#    #+#             */
/*   Updated: 2024/06/03 12:47:52 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char **environ;

int find_env_var(const char *name) {
	int len = strlen(name);
	for (int i = 0; environ[i] != NULL; i++) {
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return i;
	}
	return -1;
}

void shell_unset(Token *args)
{
	if (args[1].value == NULL) {
		fprintf(stderr, "minishell: expected argument to \"unset\"\n");
		return;
	}
	int index = find_env_var(args[1].value);
	if (index == -1) {
		fprintf(stderr, "minishell: environment variable '%s' not found\n", args[1].value);
		return;
	}
	free(environ[index]);
	// Shift the remaining variables up by one
	for (int i = index; environ[i] != NULL; i++) {
		environ[i] = environ[i + 1];
	}
}

// int main()
// {
//	 int status;
//	 char *args[] = {"unset", "my_variable", NULL};

// 	status = shell_unset(args);
//	 if (status != 0)
// 	{
//		 fprintf(stderr, "Error executing unset command\n");
//		 return 1;
//	 }
//	 printf("Unset command executed successfully\n");
//	 return 0;
// }