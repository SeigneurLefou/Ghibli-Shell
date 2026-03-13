<<<<<<< HEAD
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

typedef enum e_tokeniser_error
{
	tokeniser_error_succes,
	tokeniser_error_unterminated_quoted_string,
} t_tokeniser_error;

t_tokeniser_error tokenise(char *expr, t_vec *command);

int	main(int argc, char **argv, char **env)
{
	char *test;

	test = readline("coucou\nsalut\nbonjour\n");
	printf("%s\n", test);
}

/*int	main(int argc, char **argv, char **env)
{
	t_vec	vec;
	t_vec parsed;
	t_tokeniser_error result = tokenise(argv[1], &parsed);
	if (result == tokeniser_error_succes)
		printf("Parser success\n");
	if (result == tokeniser_error_unterminated_quoted_string)
		printf("Parser error: Unterminated quoted string.\n");

	unsigned int i = 0;
	while (i < parsed.size) {
		t_vec cmd = *(t_vec *)vec_get(&parsed, i);
		write(1, (char *)cmd.data, cmd.size);
		write(1, "\n", 1);
		vec_free(&cmd);
		i++;
	}

	vec_truncate(&vec);

	for (unsigned int i = 0; i < 100000000; i++)
	{
		vec_get(&vec, &a);
	}

	vec_free(&vec);
}*/
