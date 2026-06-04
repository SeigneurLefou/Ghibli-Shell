/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:49:23 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 18:50:27 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	is_a_delimiter(t_token *token, bool match_all, bool match_pipe)
{
	return (token->type == token_type_scope_delimiter
		&& ((token->data.data[0] == '&' || (!match_pipe
					&& (token->data.data[0] == '|' && token->data.size == 2))
				|| (match_pipe && token->data.data[0] == '|')
				|| token->data.data[0] == ';') || match_all));
}

/* 0 = error */
/* From right to left */
int	get_matching_parenthese(t_vec *expr, unsigned int index)
{
	int		count;
	t_token	*token;

	count = 0;
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			break ;
		index--;
	}
	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index--);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			count--;
		if (count == 0)
			return (index + 1);
	}
	return (0);
}

/* From right to left */
int	get_next_parenthese(t_vec *expr, unsigned int index)
{
	t_token	*token;

	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			break ;
		index--;
	}
	return (index);
}

/* From right to left */
int	get_next_delimiter(t_vec *expr, unsigned int index)
{
	t_token	*token;

	while (index > 0)
	{
		token = (t_token *)vec_get(expr, index);
		if (is_a_delimiter(token, true, true))
			break ;
		index--;
	}
	return (index);
}

bool	check_closing_parentheses(t_vec *expr, unsigned int end,
		unsigned int index)
{
	t_token	*token;
	int		count;

	count = 0;
	while (index < end)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			count--;
		if (count <= 0)
			return (false);
		index++;
	}
	return (true);
}
