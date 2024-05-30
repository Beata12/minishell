/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 07:43:12 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/30 12:42:25 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int main(int argc, char **argv) 
{
    int i;

    if (argc > 2)
	{
        if (strcmp(argv[2], "\"") == 0)
		{
            printf("argv[2] jest równy podwójnemu cudzysłowowi\n");
            i = 3;
            while (i < argc && strcmp(argv[i], "\"") != 0)
			{
                printf(" %s", argv[i]);
                i++;
            }
            printf("\n");
        }
    }
	else
        printf("You need some arguments\n");
    return 0;
}