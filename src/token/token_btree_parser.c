#include "token.h"

/* 0 = error */
int	get_matching_parethese(t_vec *expr, unsigned int index)
{
	int	count;
	t_token			*token;

	count = 0;
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			count--;
		if (count == 0)
			return (index);
		index--;
	}
	return (0);
}

bool	is_a_delimiter(t_token *token)
{
	return (token->type == token_type_scope_delimiter
		&& (token->data.data[0] == '&' || token->data.data[0] == '|'
			|| token->data.data[0] == ';'));
}

bool	is_in_parentheses(t_vec *expr, unsigned int index, unsigned int end)
{
	int	count;
	t_token			*token;

	token = (t_token *)vec_get(expr, index);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != '(')
		return (false);
	token = (t_token *)vec_get(expr, end);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != ')')
		return (false);
	count = 0;
	while (index < end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			count--;
		if (count <= 0)
			return (false);
		index++;
	}
	return (true);
}

bool	contains_scope_delimiter(t_vec *expr, t_btree_node *node)
{
	unsigned int	index;
	t_token			*token;
	int parenthese_count = 0;

	// TODO: Maybe remove the parenthese counter? IDK if it's usefull.
	index = node->expr_start;
	while (index <= node->expr_stop)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			parenthese_count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			parenthese_count--;
		if (is_a_delimiter(token) && !parenthese_count)
			return (true);
		index++;
	}
	return (false);
}

bool	parse_token_btree(t_vec *expr, t_btree_node *node)
{
	t_btree_node	*btree_a;
	t_btree_node	*btree_b;
	unsigned int	expr_stop;
	t_token			*token;

	if (is_in_parentheses(expr, node->expr_start, node->expr_stop))
	{
		node->expr_start++;
		node->expr_stop--;
	}
	if (!contains_scope_delimiter(expr, node))
	{
		node->expr_start = node->expr_start;
		node->expr_stop = node->expr_stop;
		node->operator = operator_none;
		node->left = NULL;
		node->right = NULL;
		return (true);
	}
	btree_a = malloc(sizeof(t_btree_node));
	btree_b = malloc(sizeof(t_btree_node));
	// TODO: Handle malloc fail
	expr_stop = node->expr_stop;
	btree_a->expr_start = node->expr_start;
	token = (t_token *)vec_get(expr, expr_stop);
	unsigned int operator_index;
	if (token->data.data[0] == ')')
	{
		expr_stop = get_matching_parethese(expr, node->expr_stop);
		if (!expr_stop)
		{
			printf("Parsing error my bro.\n");
			// TODO: It leaks here bro
			return (false);
		}
		btree_b->expr_stop = node->expr_stop;
		operator_index = expr_stop - 1;
	}
	else
	{
		while (token && !is_a_delimiter(token))
		{
			expr_stop--;
			token = (t_token *)vec_get(expr, expr_stop);
		}
		operator_index = expr_stop;
		btree_b->expr_stop = node->expr_stop;
	}
	btree_a->expr_stop = operator_index - 1;
	btree_b->expr_start = operator_index + 1;
	node->left = btree_a;
	node->right = btree_b;
	if (!parse_token_btree(expr, node->left))
		return (false);
	if (!parse_token_btree(expr, node->right))
		return (false);
	token = (t_token *)vec_get(expr, operator_index);
	if (token->data.data[0] == '&')
		node->operator= operator_and;
	else if (token->data.data[0] == '|')
		node->operator= operator_or;
	else if (token->data.data[0] == ';')
		node->operator= operator_semicolon;
	return (true);
}
