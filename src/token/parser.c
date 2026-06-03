/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:46:29 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 19:14:41 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	create_children_nodes(t_vec *expr, t_btree_node *node,
		unsigned int *operator_index, unsigned int depth)
{
	t_btree_node	*btree_a;
	t_btree_node	*btree_b;
	unsigned int	expr_end;

	btree_a = mem_alloc(sizeof(t_btree_node), default_error_exit, NULL, 0b1);
	btree_b = mem_alloc(sizeof(t_btree_node), default_error_exit, NULL, 0b1);
	expr_end = node->expr_end;
	btree_a->expr_start = node->expr_start;
	*operator_index = capture_scope(expr, btree_b, node, expr_end);
	btree_a->expr_end = *operator_index - 1;
	btree_b->expr_start = *operator_index + 1;
	vec_null(&btree_a->io_files);
	vec_null(&btree_b->io_files);
	node->left = btree_a;
	node->right = btree_b;
	if (!parse_token_btree(expr, node->left, depth + 1))
		return (false);
	if (!parse_token_btree(expr, node->right, depth + 1))
		return (false);
	return (true);
}

void	set_node_operator(t_vec *expr, t_btree_node *node,
		unsigned int operator_index)
{
	t_token	*token;

	token = (t_token *)vec_get(expr, operator_index);
	if (token->type == token_type_scope_delimiter && token->data.data[0] == '&')
		node->operator = operator_and;
	else if (token->type == token_type_scope_delimiter
		&& token->data.data[0] == '|' && token->data.size == 2)
		node->operator = operator_or;
	else if (token->type == token_type_scope_delimiter
		&& token->data.data[0] == ';')
		node->operator = operator_semicolon;
	else if (token->type == token_type_scope_delimiter
		&& token->data.data[0] == '|')
		node->operator = operator_pipe;
}

bool	parse_token_btree(t_vec *expr, t_btree_node *node, unsigned int depth)
{
	unsigned int	operator_index;

	if (depth > 1024)
		return (false);
	if (is_in_parentheses(expr, node->expr_start, node->expr_end))
	{
		enter_parenthese(expr, node);
		return (parse_token_btree(expr, node, depth + 1));
	}
	if (!contains_scope_delimiter(expr, node, false))
	{
		set_leaf(expr, node);
		return (true);
	}
	if (!create_children_nodes(expr, node, &operator_index, depth))
		return (false);
	set_node_operator(expr, node, operator_index);
	return (true);
}
