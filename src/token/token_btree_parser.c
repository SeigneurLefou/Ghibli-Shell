/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_btree_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:28:24 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 17:37:29 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	contains_scope_delimiter(t_vec *expr, t_token_btree_node *node)
{
	unsigned int	index;
	t_token			*token;

	index = node->expr_start;
	while (index <= node->expr_stop)
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
	unsigned int		expr_stop;
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
	expr_stop = node->expr_start;
	btree_a->expr_start = node->expr_start;
	token = (t_token *)vec_get(expr, expr_stop);
	if (token->data.data[0] == '(')
	{
		expr_stop = get_matching_parethese(expr, node->expr_start, node->expr_stop) + node->expr_start;
		if (!expr_stop)
			printf("Parsing error my bro.");
		btree_a->expr_start ++;
	}
	else
	{
		while (!is_a_delimiter(token))
		{
			expr_stop++;
			token = (t_token *)vec_get(expr, expr_stop);
		}
	}
	btree_a->expr_stop = expr_stop - 1;
	btree_b->expr_start = expr_stop + 1;
	btree_b->expr_stop = node->expr_stop;
	node->left = btree_a;
	node->right = btree_b;
	parse_token_btree(expr, node->left);
	parse_token_btree(expr, node->right);
	token = (t_token *)vec_get(expr, expr_stop);
	if (token->data.data[0] == '&')
		node->operator= operator_and;
	else if (token->data.data[0] == '|')
		node->operator= operator_or;
	else if (token->data.data[0] == ';')
		node->operator= operator_semicolon;
}
