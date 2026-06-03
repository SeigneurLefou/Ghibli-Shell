/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:43:04 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 17:13:48 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	is_char_delimiter(t_token *token)
{
	return (token->data.data[0] == '&' || token->data.data[0] == '|'
		|| token->data.data[0] == ';');
}

t_parsing_check_result	check_unsuported_operators(t_vec *expr)
{
	unsigned int	index;
	t_token			*token;

	index = 0;
	while (index < expr->size)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && (token->data.size == 1
				&& (token->data.data[0] == '&' || token->data.data[0] == ';')))
			return ((t_parsing_check_result){parse_err_unsupported_operator,
				index, index});
		index++;
	}
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}

t_parsing_check_result	check_syntax_first(t_vec *expr)
{
	t_parsing_check_result	result;

	result = check_matching_parentheses(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	result = check_unsuported_operators(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	result = check_empty_parentheses(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	result = check_missing_operand(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}

t_parsing_check_result	check_syntax(t_vec *expr)
{
	t_parsing_check_result	result;

	result = check_syntax_first(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	result = check_unsuported_arithmetic(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	result = check_no_operator_parentheses(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	result = check_io_files_after_parentheses(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	result = check_io_files(expr);
	if (result.parsing_error != parse_err_success)
		return (result);
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}
