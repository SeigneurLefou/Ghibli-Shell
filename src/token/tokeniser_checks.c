/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:43:15 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 14:04:18 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	tokenise_check_quotes(char *expr, unsigned int *i,
		t_token *current_token, char *quote_char)
{
	if (expr[*i] == '\\' && expr[*i + 1])
	{
		set_expand(current_token, false, false);
		push_char(current_token, expr[++*i]);
		return (true);
	}
	else if (expr[*i] == '"')
	{
		push_char(current_token, 0);
		*quote_char = '"';
		current_token->no_skip = true;
		set_expand(current_token, false, false);
		return (true);
	}
	else if (expr[*i] == '\'')
	{
		push_char(current_token, 0);
		*quote_char = '\'';
		current_token->no_skip = true;
		set_expand(current_token, false, false);
		return (true);
	}
	return (false);
}

bool	tokenise_check_expands(char *expr, unsigned int *i,
		t_token *current_token)
{
	if (expr[*i] == '*')
	{
		push_char(current_token, expr[*i]);
		set_expand(current_token, true, false);
		set_expand(current_token, false, false);
		return (true);
	}
	else if (expr[*i] == '$' && (is_valid_expand_char(expr[*i + 1]) || expr[*i
			+ 1] == '?'))
	{
		push_char(current_token, expr[*i]);
		set_expand(current_token, true, true);
		return (true);
	}
	else if (expr[*i] == '~' && current_token->type == token_type_void
		&& is_tilde_escape_compatible(expr[*i + 1]))
	{
		push_char(current_token, expr[*i]);
		set_expand(current_token, true, false);
		set_expand(current_token, false, false);
		return (true);
	}
	return (false);
}

bool	tokenise_check_delimiters(char *expr, unsigned int *i,
		t_token *current_token, t_vec *command)
{
	if (expr[*i] == '(' || expr[*i] == ')' || expr[*i] == ';')
	{
		add_simple_token(expr, *i, command, current_token);
		return (true);
	}
	else if (expr[*i] == '&' || expr[*i] == '|')
	{
		add_double_token(expr, i, command, current_token,
			token_type_scope_delimiter);
		return (true);
	}
	else if (expr[*i] == '>' || expr[*i] == '<')
	{
		add_double_token(expr, i, command, current_token,
			token_type_command_delimiter);
		return (true);
	}
	else if (ft_isspace(expr[*i]))
	{
		append_token(command, current_token, token_type_plain);
		return (true);
	}
	return (false);
}
