/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:47:41 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 14:09:43 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	parse_token_double_quote_no_escape(char *expr, unsigned int *i,
		t_token *current_token, char *quote_char)
{
	if (expr[*i] == '$' && (is_valid_expand_char(expr[(*i) + 1]) || expr[(*i)
				+ 1] == '?'))
	{
		push_char(current_token, expr[*i]);
		set_expand(current_token, true, false);
	}
	else if (expr[*i] == '"')
	{
		(*quote_char) = 0;
		set_expand(current_token, false, false);
	}
	else
	{
		if (current_token->is_expand && expr[(*i) - 1] == '?')
			set_expand(current_token, false, false);
		else if (!is_valid_expand_char(expr[*i]) && expr[*i] != '?')
			set_expand(current_token, false, false);
		push_char(current_token, expr[*i]);
	}
}

void	parse_token_double_quote(char *expr, unsigned int *i,
		t_token *current_token, char *quote_char)
{
	char	escaped_char;

	if (expr[*i] == '\\' && expr[(*i) + 1])
	{
		set_expand(current_token, false, false);
		(*i)++;
		if (is_escape(expr[*i], *quote_char))
		{
			escaped_char = get_escape(expr[*i]);
			push_char(current_token, escaped_char);
		}
		else
		{
			push_char(current_token, '\\');
			push_char(current_token, expr[*i]);
		}
	}
	else
		parse_token_double_quote_no_escape(expr, i, current_token, quote_char);
}

void	parse_token_simple_quote(char *expr, unsigned int *i,
		t_token *current_token, char *quote_char)
{
	if (expr[*i] == '\'')
		(*quote_char) = 0;
	else
		push_char(current_token, expr[*i]);
}
