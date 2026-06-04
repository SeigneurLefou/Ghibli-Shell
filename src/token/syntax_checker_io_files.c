/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_io_files.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:06:18 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 17:39:58 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_parsing_check_result	check_io_file(t_vec *expr, unsigned int *index,
		unsigned int par_index, t_token	**token)
{
	(*token) = (t_token *)vec_get(expr, *index);
	if (!((*token)->type == token_type_command_delimiter
			&& ((*token)->data.data[0] == '<'
				|| (*token)->data.data[0] == '>')))
		return ((t_parsing_check_result){
			parse_err_invalide_io_file_after_parentheses,
			*index, par_index});
	(*index)++;
	(*token) = (t_token *)vec_get(expr, *index);
	if (!*token || (*token)->type != token_type_plain)
		return ((t_parsing_check_result){
			parse_err_invalide_io_file_after_parentheses,
			*index, par_index});
	(*index)++;
	(*token) = (t_token *)vec_get(expr, *index);
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}

t_parsing_check_result	check_io_files_after_parentheses(t_vec *expr)
{
	unsigned int			i;
	t_token					*token;
	unsigned int			par_index;
	t_parsing_check_result	result;

	i = 1;
	while (i < expr->size - 1)
	{
		par_index = i;
		token = (t_token *)vec_get(expr, i);
		if (token->type == token_type_scope_delimiter
			&& token->data.data[0] == ')')
		{
			token = (t_token *)vec_get(expr, ++i);
			while (i < expr->size && token->type != token_type_scope_delimiter)
			{
				result = check_io_file(expr, &i, par_index, &token);
				if (result.parsing_error != parse_err_success)
					return (result);
			}
		}
		else
			i++;
	}
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}

t_parsing_check_result	check_io_files(t_vec *expr)
{
	unsigned int	index;
	t_token			*token;

	index = 0;
	while (index < expr->size)
	{
		token = (t_token *)vec_get(expr, index);
		if (token->type == token_type_command_delimiter
			&& (token->data.data[0] == '<' || token->data.data[0] == '>'))
		{
			index++;
			token = (t_token *)vec_get(expr, index);
			if (!token || token->type != token_type_plain)
				return ((t_parsing_check_result){parse_err_invalide_io_file,
					index, index});
		}
		index++;
	}
	return ((t_parsing_check_result){parse_err_success, 0, 0});
}
