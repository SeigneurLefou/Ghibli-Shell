#include "token.h"

/* 0 = error */
unsigned int	get_matching_parethese(t_vec *expr, unsigned int index,
		unsigned int end)
{
	unsigned int	count;
	t_token			*token;

	count = 0;
	while (index < end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			count--;
		if (count == 0)
			return (index);
		index++;
	}
	return (0);
}

bool	is_a_delimiter(t_token *token)
{
	return (token->type == token_type_scope_delimiter
		&& (token->data.data[0] == '&' || token->data.data[0] == '|'
			|| token->data.data[0] == ';'));
}

bool	is_in_paretheses(t_vec *expr, unsigned int index, unsigned int end)
{
	unsigned int	count;
	t_token			*token;

	token = (t_token *)vec_get(expr, index);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != '(')
		return (false);
	token = (t_token *)vec_get(expr, end);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != ')')
		return (false);
	count = 0;
	while (index <= end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == '(')
			count++;
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
			count--;
		index++;
	}
	return (!count);
}

bool	contains_scope_delimiter(t_vec *expr, t_btree_node *node)
{
	unsigned int	index;
	t_token			*token;
	int parenthese_count = 0;

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

void	parse_token_btree(t_vec *expr, t_btree_node *node)
{
	t_btree_node	*btree_a;
	t_btree_node	*btree_b;
	unsigned int	expr_stop;
	t_token			*token;

	if (is_in_paretheses(expr, node->expr_start, node->expr_stop))
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
		return ;
	}
	btree_a = malloc(sizeof(t_btree_node));
	btree_b = malloc(sizeof(t_btree_node));
	// TODO: Handle malloc fail
	expr_stop = node->expr_start;
	btree_a->expr_start = node->expr_start;
	token = (t_token *)vec_get(expr, expr_stop);
	unsigned int operator_index;
	if (token->data.data[0] == '(')
	{
		expr_stop = get_matching_parethese(expr, node->expr_start, node->expr_stop);
		if (!expr_stop)
			printf("Parsing error my bro.");
		btree_a->expr_start ++;
		operator_index = expr_stop + 1;
	}
	else
	{
		while (token && !is_a_delimiter(token))
		{
			expr_stop++;
			token = (t_token *)vec_get(expr, expr_stop);
		}
		operator_index = expr_stop;
	}
	btree_a->expr_stop = expr_stop - 1;
	btree_b->expr_start = operator_index + 1;
	btree_b->expr_stop = node->expr_stop;
	node->left = btree_a;
	node->right = btree_b;
	parse_token_btree(expr, node->left);
	parse_token_btree(expr, node->right);
	token = (t_token *)vec_get(expr, operator_index);
	if (token->data.data[0] == '&')
		node->operator= operator_and;
	else if (token->data.data[0] == '|')
		node->operator= operator_or;
	else if (token->data.data[0] == ';')
		node->operator= operator_semicolon;
}
