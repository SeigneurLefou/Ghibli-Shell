/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:53:16 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 11:04:41 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char *test;

	test = readline("coucou\nsalut\nbonjour\n");
	printf("%s\n", test);
}

/*int	main(int argc, char **argv, char **env)
{
	t_vec	vec;

	vec_init(&vec, sizeof(int), 100000);
	int a = 1;
	for (unsigned int i = 0; i < 1000000; i++)
	{
		vec_append(&vec, &a);
	}

	vec_truncate(&vec);

	for (unsigned int i = 0; i < 100000000; i++)
	{
		vec_get(&vec, &a);
	}

	vec_free(&vec);
}*/
