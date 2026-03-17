#include "parser.h"

/* 0 = error */
unsigned int	get_matching_parethese(t_vec *expr, unsigned int index,
		unsigned int end)
{
	unsigned int	count;
	t_token			*token;

	count = 1;
	while (index < end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->data.data[0] == '(')
			count++;
		if (token->data.data[0] == '(')
			count--;
		if (count == 0)
			return (index);
	}
	return (0);
}

bool	is_a_delimiter(t_token *token)
{
	return (token->type == token_type_scope_delimiter
		&& (token->data.data[0] == '&' || token->data.data[0] == '|'
			|| token->data.data[0] == ';'));
}

bool	contains_scope_delimiter(t_vec *expr, t_token_btree_node *node)
{
	unsigned int	index;
	t_token			*token;

	index = node->expr_start;
	while (index < node->expr_stop)
	{
		token = (t_token *)vec_get(expr, index);
		if (is_a_delimiter(token))
			return (true);
		index++;
	}
	return (false);
}

void	parse_token_btree(t_vec *expr, t_token_btree_node *node)
{
	t_token_btree_node	*btree_a;
	t_token_btree_node	*btree_b;
	unsigned int		cmd_stop;
	t_token				*token;

	if (!contains_scope_delimiter(expr, node))
	{
		node->expr_start = node->expr_start;
		node->expr_stop = node->expr_stop;
		node->operator = operator_none;
		node->left = NULL;
		node->right = NULL;
		return ;
	}
	btree_a = malloc(sizeof(t_token_btree_node));
	btree_b = malloc(sizeof(t_token_btree_node));
	// TODO: Handle malloc fail
	cmd_stop = node->expr_start;
	token = (t_token *)vec_get(expr, cmd_stop);
	while (!is_a_delimiter(token))
	{
		cmd_stop++;
		token = (t_token *)vec_get(expr, cmd_stop);
	}
	btree_a->expr_stop = cmd_stop - 1;
	btree_a->expr_start = node->expr_start;
	btree_b->expr_start = cmd_stop + 1;
	btree_b->expr_stop = node->expr_stop;
	node->left = btree_a;
	node->right = btree_b;
	parse_token_btree(expr, node->left);
	parse_token_btree(expr, node->right);
	token = (t_token *)vec_get(expr, cmd_stop);
	if (token->data.data[0] == '&')
		node->operator= operator_and;
	else if (token->data.data[0] == '|')
		node->operator= operator_or;
	else if (token->data.data[0] == ';')
		node->operator= operator_semicolon;
}
