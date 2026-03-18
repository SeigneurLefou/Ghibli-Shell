#include "minishell.h"


void print_tree(t_vec *expr, t_btree_node *node)
{
	if (node->operator == operator_none)
	{
		for (int i = node->expr_start; i <= node->expr_stop; i++)
		{
			t_token *token = (t_token *)vec_get(expr, i);
			write(1, token->data.data, token->data.size);
			write(1, " ", 1);
		}
		free(node);
	}
	else
	{
		write(1, "(", 1);
		print_tree(expr, node->left);
		if (node->operator == operator_and)
			write(1, " and ", 6);
		if (node->operator == operator_or)
			write(1, " or ", 5);
		if (node->operator == operator_semicolon)
			write(1, "; ", 3);
		print_tree(expr, node->right);
		write(1, ")", 1);
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
	t_btree_node *root = malloc(sizeof(t_btree_node));
	root->expr_start = 0;
	root->expr_stop = parsed.size - 1;
	parse_token_btree(&parsed, root);

	print_tree(&parsed, root);
	
	for (unsigned int i = 0; i < parsed.size; i++)
	{
		vec_free(&((t_token *)vec_get(&parsed, i))->data);
	}
	vec_free(&parsed);
}
