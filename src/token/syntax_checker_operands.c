/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_operands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:04:39 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 17:12:23 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_parsing_check_result	check_missing_operand_parentheses(t_vec *expr,
		t_token *token, unsigned int index)
{
	if ((token->type == token_type_scope_delimiter
			&& (token->data.data[0] == '&' || token->data.data[0] == '|'
				|| token->data.data[0] == ';' || token->data.data[0] == '(')))
		return ((t_parsing_check_result){parse_err_bad_left_operand, index,
			index - 1});
	token = (t_token *)vec_get(expr, index + 1);
	if ((token->type == token_type_scope_delimiter
			&& (token->data.data[0] == '&' || token->data.data[0] == '|'
				|| token->data.data[0] == ';' || token->data.data[0] == ')')))
		return ((t_parsing_check_result){parse_err_bad_right_operand, index,
			index + 1});
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}

t_parsing_check_result	check_missing_operand(t_vec *expr)
{
	unsigned int			index;
	t_token					*token;
	t_parsing_check_result	result;

	index = 0;
	while (index < expr->size)
	{
		token = (t_token *)vec_get(expr, index);
		if ((token->type == token_type_scope_delimiter
				&& is_char_delimiter(token)))
		{
			if (index == 0)
				return ((t_parsing_check_result){parse_err_bad_left_operand, 0,
					1});
			if (index == expr->size - 1)
				return ((t_parsing_check_result){parse_err_bad_right_operand,
					expr->size - 1, expr->size - 1});
			token = (t_token *)vec_get(expr, index - 1);
			result = check_missing_operand_parentheses(expr, token, index);
			if (result.parsing_error != parse_err_success)
				return (result);
		}
		index++;
	}
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}

static t_parsing_check_result	check_no_operator_parentheses_right(t_vec *expr,
		unsigned int index)
{
	t_token	*token;

	token = (t_token *)vec_get(expr, index + 1);
	if (!((token->type == token_type_scope_delimiter
				&& (is_char_delimiter(token) || token->data.data[0] == ')'))
			|| token->type == token_type_command_delimiter))
		return ((t_parsing_check_result){parse_err_no_operator_right_parenthese,
			index, index + 1});
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}

static t_parsing_check_result	check_no_operator_parentheses_left(t_vec *expr,
		unsigned int index)
{
	t_token	*token;

	token = (t_token *)vec_get(expr, index - 1);
	if (!(token->type == token_type_scope_delimiter && (is_char_delimiter(token)
				|| token->data.data[0] == '(')))
		return ((t_parsing_check_result){parse_err_no_operator_left_parenthese,
			index, index - 1});
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}

t_parsing_check_result	check_no_operator_parentheses(t_vec *expr)
{
	unsigned int			index;
	t_token					*token;
	t_parsing_check_result	result;

	index = 1;
	while (index < expr->size - 1)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
		{
			result = check_no_operator_parentheses_left(expr, index);
			if (result.parsing_error != parse_err_success)
				return (result);
		}
		else if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
		{
			result = check_no_operator_parentheses_right(expr, index);
			if (result.parsing_error != parse_err_success)
				return (result);
		}
		index++;
	}
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}
