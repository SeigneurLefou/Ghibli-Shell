/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:53:16 by lchamard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/03/17 17:34:49 by lchamard         ###   ########.fr       */
=======
/*   Updated: 2026/03/17 15:15:58 by yben-dje         ###   ########.fr       */
>>>>>>> 045c2aa ([Parser] Start support for parentheses)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_tree(t_vec *expr, t_token_btree_node *node)
{
	if (node->operator == operator_none)
	{
		for (int i = node->expr_start; i <= node->expr_stop; i++)
		{
			t_token *token = (t_token *)vec_get(expr, i);
			write(1, token->data.data, token->data.size);
			write(1, " - ", 3);
		}
		
		write(1, "\n", 1);
	}
	else
	{
		print_tree(expr, node->left);
		if (node->operator == operator_and)
			printf("Operator: And\n");
		if (node->operator == operator_or)
			printf("Operator: Or\n");
		if (node->operator == operator_semicolon)
			printf("Operator: Semicolon\n");
		print_tree(expr, node->right);
	}
}

int	main(int argc, char **argv, char **env)
{
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

	print_tree(&parsed, &root);
	
	vec_free(&parsed);
}

