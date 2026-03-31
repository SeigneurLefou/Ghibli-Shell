/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:43:04 by yben-dje          #+#    #+#             */
/*   Updated: 2026/03/31 19:17:12 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_parsing_checker_result	check_matching_parentheses(t_vec *expr)
{
	int		count;
	t_token	*token;
	int		index;
	int 	par_index;

	count = 0;
	index = 0;
	par_index = -1; 
	while (index < expr->size)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
		{
			if (par_index < 0)
				par_index = index;
			count++;
		}
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			count--;
		if (!count)
			par_index = -1;
		if (count < 0)
			return ((t_parsing_checker_result){parsing_error_unmatching_parentheses,
				index, -1});
		index++;
	}
	if (count)
		return ((t_parsing_checker_result){parsing_error_unmatching_parentheses,
			par_index, index});
	return ((t_parsing_checker_result){parsing_error_success, 0, 0});
}

unsigned int	get_matching_parentheses_left(t_vec *expr, unsigned int index)
{
	int		count;
	t_token	*token;

	count = 1;
	index++;
	while (index < expr->size && count)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
			count++;
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
			count--;
		index++;
	}
	return (index);
}

t_parsing_checker_result	check_unsuported_arithmetic(t_vec *expr)
{
	unsigned int	index;
	t_token			*token1;
	t_token			*token2;
	unsigned int	matching1;
	unsigned int	matching2;

	index = 0;
	while (index < expr->size)
	{
		token1 = (t_token *)vec_get(expr, index);
		token2 = (t_token *)vec_get(expr, index + 1);
		if (token1->type == token_type_scope_delimiter
			&& token1->data.data[0] == '('
			&& token2->type == token_type_scope_delimiter
			&& token2->data.data[0] == '(')
		{
			matching1 = get_matching_parentheses_left(expr, index);
			matching2 = get_matching_parentheses_left(expr, index + 1);
			if (matching2 + 1 == matching1)
				return ((t_parsing_checker_result){parsing_error_unsuported_arithmetic,
					index, matching1 - 1});
		}
		index++;
	}
	return ((t_parsing_checker_result){parsing_error_success, 0, 0});
}

t_parsing_checker_result	check_empty_parentheses(t_vec *expr)
{
	unsigned int	index;
	t_token			*token;

	index = 0;
	while (index < expr->size)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
		{
			token = (t_token *)vec_get(expr, index + 1);
			if (token->type == token_type_scope_delimiter
				&& token->data.data[0] == ')')
				return ((t_parsing_checker_result){parsing_error_empty_parentheses,
					index, index + 1});
		}
		index++;
	}
	return ((t_parsing_checker_result){parsing_error_success, 0, 0});
}

t_parsing_checker_result	check_missing_operand(t_vec *expr)
{
	unsigned int	index;
	t_token			*token;

	index = 0;
	while (index < expr->size)
	{
		token = (t_token *)vec_get(expr, index);
        if ((token->type == token_type_scope_delimiter && (token->data.data[0] == '&' || token->data.data[0] == '|' || token->data.data[0] == ';')))
        {
            if (index == 0)
                return ((t_parsing_checker_result){parsing_error_incorrect_left_operand, 0, 1});
            if (index == expr->size - 1)
                return ((t_parsing_checker_result){parsing_error_incorrect_right_operand, expr->size - 1, 1});
            token = (t_token *)vec_get(expr, index - 1);
            if ((token->type == token_type_scope_delimiter && (token->data.data[0] == '&' || token->data.data[0] == '|' || token->data.data[0] == ';' || token->data.data[0] == '(')))
                return ((t_parsing_checker_result){parsing_error_incorrect_left_operand, index - 1, index});
            token = (t_token *)vec_get(expr, index + 1);
            if ((token->type == token_type_scope_delimiter && (token->data.data[0] == '&' || token->data.data[0] == '|' || token->data.data[0] == ';' || token->data.data[0] == ')')))
                return ((t_parsing_checker_result){parsing_error_incorrect_right_operand, index + 1, index});
        }
        index++;
	}
	return ((t_parsing_checker_result){parsing_error_success, 0, 0});
}

t_parsing_checker_result	check_no_operator_parentheses(t_vec *expr)
{
	unsigned int	index;
	t_token			*token;

	index = 1;
	while (index < expr->size - 1)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == '(')
		{
			token = (t_token *)vec_get(expr, index - 1);
			if (!((token->type == token_type_scope_delimiter && (token->data.data[0] == '&' || token->data.data[0] == '|' || token->data.data[0] == ';' || token->data.data[0] == '('))))
				return ((t_parsing_checker_result){parsing_error_no_operator_left_parenthese,
					index, index - 1});
		}
		else if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
		{
			token = (t_token *)vec_get(expr, index + 1);
			if (!((token->type == token_type_scope_delimiter && (token->data.data[0] == '&' || token->data.data[0] == '|' || token->data.data[0] == ';' || token->data.data[0] == ')')) || token->type == token_type_command_delimiter))
				return ((t_parsing_checker_result){parsing_error_no_operator_right_parenthese,
					index, index + 1});
		}
		index++;
	}
	return ((t_parsing_checker_result){parsing_error_success, 0, 0});
}

t_parsing_checker_result	check_io_files_after_parentheses(t_vec *expr)
{
	unsigned int	index;
	t_token			*token;
	unsigned int 	par_index;

	index = 1;
	while (index < expr->size - 1)
	{
		par_index = index;
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_scope_delimiter && token->data.data[0] == ')')
		{
			token = (t_token *)vec_get(expr, ++index);
			while (index < expr->size && token->type != token_type_scope_delimiter)
			{
				token = (t_token *)vec_get(expr, index);
				if (!(token->type == token_type_command_delimiter && (token->data.data[0] == '<' || token->data.data[0] == '>')))
					return ((t_parsing_checker_result){parsing_error_invalide_io_file_after_parentheses, index, par_index});
				index ++;
				token = (t_token *)vec_get(expr, index);
				if (!token || token->type != token_type_plain)
					return ((t_parsing_checker_result){parsing_error_invalide_io_file_after_parentheses, index, par_index});
				index ++;
				token = (t_token *)vec_get(expr, index);
			}
		}
		else
			index++;
	}
	return ((t_parsing_checker_result){parsing_error_success, 0, 0});
}

t_parsing_checker_result	check_io_files(t_vec *expr)
{
	unsigned int	index;
	t_token			*token;

	index = 0;
	while (index < expr->size)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_command_delimiter && (token->data.data[0] == '<' || token->data.data[0] == '>'))
		{
			index ++;
			token = (t_token *)vec_get(expr, index);
			if (!token || token->type != token_type_plain)
				return ((t_parsing_checker_result){parsing_error_invalide_io_file, index, index});
		}
		index++;
	}
	return ((t_parsing_checker_result){parsing_error_success, 0, 0});
}

t_parsing_checker_result    check_syntax(t_vec *expr)
{
    t_parsing_checker_result result;
    
    result = check_matching_parentheses(expr);
	if (result.parsing_error != parsing_error_success)
		return (result);
    result = check_empty_parentheses(expr);
	if (result.parsing_error != parsing_error_success)
		return (result);
    result = check_missing_operand(expr);
	if (result.parsing_error != parsing_error_success)
		return (result);
    result = check_unsuported_arithmetic(expr);
	if (result.parsing_error != parsing_error_success)
		return (result);
    result = check_no_operator_parentheses(expr);
	if (result.parsing_error != parsing_error_success)
		return (result);
	result = check_io_files_after_parentheses(expr);
	if (result.parsing_error != parsing_error_success)
		return (result);
	result = check_io_files(expr);
	if (result.parsing_error != parsing_error_success)
		return (result);
    return ((t_parsing_checker_result){parsing_error_success, 0, 0});
}
