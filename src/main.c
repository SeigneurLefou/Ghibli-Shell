/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:53:16 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 14:20:00 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_vec	vec;
	t_vec parsed;
	t_tokeniser_error result = tokenise(argv[1], &parsed);
	if (result == tokeniser_error_succes)
		printf("Parser success\n");
	if (result == tokeniser_error_unterminated_quoted_string)
		printf("Parser error: Unterminated quoted string.\n");

	unsigned int i = 0;
	while (i < parsed.size)
	{
		t_token cmd = *(t_token *)vec_get(&parsed, i);
		if (cmd.type == token_type_plain)
			write(1, "Plain:     ", 12);
		else
			write(1, "Delimiter: ", 12);
		write(1, (char *)cmd.data.data, cmd.data.size);
		write(1, "\n", 1);
		i++;
	}
	t_token_btree_node root;
	root.expr_start = 0;
	root.expr_stop = parsed.size - 1;
	parse_token_btree(&parsed, &root);

	printf("%d - %d \n", root.left->expr_start, root.left->expr_stop);
	printf("%d - %d \n", root.right->expr_start, root.right->expr_stop);

	for (int i = root.left->expr_start; i <= root.left->expr_stop; i ++)
	{
		printf("%s - ", ((t_token *)vec_get(&parsed, i))->data.data);
	}
	printf("\n------------------\n\n");
	for (int i = root.right->expr_start; i <= root.right->expr_stop; i ++)
	{
		printf("%s - ", ((t_token *)vec_get(&parsed, i))->data.data);
	}
	printf("\n");

	if (root.operator == operator_and)
		printf("Operator: And\n");
	if (root.operator == operator_or)
		printf("Operator: Or\n");
	if (root.operator == operator_semicolon)
		printf("Operator: Semicolon\n");
	vec_free(&parsed);
}
