/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scops_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:51:20 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 19:14:59 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/* From right to left */
bool	is_in_parentheses(t_vec *expr, unsigned int index, unsigned int end)
{
	t_token	*token;

	token = (t_token *)vec_get(expr, index);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != '(')
		return (false);
	while (end > 0)
	{
		token = (t_token *)vec_get(expr, end);
		if (is_a_delimiter(token, false, true))
			return (false);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			break ;
		end--;
	}
	token = (t_token *)vec_get(expr, end);
	if (token->type != token_type_scope_delimiter || token->data.data[0] != ')')
		return (false);
	if (!check_closing_parentheses(expr, end, index))
		return (false);
	return (true);
}

/* From left to right */
bool	contains_scope_delimiter(t_vec *expr, t_btree_node *node,
		bool match_all)
{
	unsigned int	index;
	t_token			*token;
	int				parenthese_count;

	parenthese_count = 0;
	index = node->expr_start;
	while (index <= node->expr_end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			parenthese_count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			parenthese_count--;
		if (is_a_delimiter(token, match_all, true) && !parenthese_count)
			return (true);
		index++;
	}
	return (false);
}

bool	contains_non_pipe_delimiter(t_vec *expr, unsigned int start,
		unsigned int stop)
{
	unsigned int	index;
	t_token			*token;
	int				parenthese_count;

	parenthese_count = 0;
	index = start;
	while (index <= stop)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			parenthese_count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			parenthese_count--;
		if (is_a_delimiter(token, false, false) && !parenthese_count)
			return (true);
		index++;
	}
	return (false);
}

unsigned int	capture_scope(t_vec *expr, t_btree_node *btree_b,
		t_btree_node *node, unsigned int expr_end)
{
	t_token			*token;
	unsigned int	operator_index;
	bool			contains_non_pipe;

	token = (t_token *)vec_get(expr, get_next_delimiter(expr, expr_end));
	if (token->data.data[0] == ')')
	{
		expr_end = get_matching_parenthese(expr, node->expr_end);
		btree_b->expr_end = node->expr_end;
		operator_index = expr_end - 1;
	}
	else
	{
		token = (t_token *)vec_get(expr, expr_end);
		contains_non_pipe = contains_non_pipe_delimiter(expr, node->expr_start,
				node->expr_end);
		while (token && (!is_a_delimiter(token, false, !contains_non_pipe)))
		{
			expr_end--;
			token = (t_token *)vec_get(expr, expr_end);
		}
		operator_index = expr_end;
		btree_b->expr_end = node->expr_end;
	}
	return (operator_index);
}

void	enter_parenthese(t_vec *expr, t_btree_node *node)
{
	unsigned int	old_stop;

	old_stop = node->expr_end;
	node->expr_end = get_next_parenthese(expr, node->expr_end) - 1;
	node->expr_start++;
	grab_io_files(expr, node, old_stop, node->expr_end + 2);
}
