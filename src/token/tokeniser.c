/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:28:21 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/26 13:48:00 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool append_token(t_vec *command, t_token *token, t_token_type type)
{
	if (token->type != token_type_void)
	{
		token->type = type;
		if (!vec_append(command, token))
			return (false);
	}
	token->type = token_type_void;
	return (true);
}

bool push_char(t_token *token, char c)
{
	if (token->type == token_type_void)
	{
		token->type = token_type_plain;
		if (!vec_init(&token->data, sizeof(char), 16))
			return (false);
	}	
	if (c)
		if (!vec_append(&token->data, &c))
			return (false);
	return (true);
}

char get_escape(char escaped_char)
{
	if (escaped_char == '\\')
		return ('\\');
	if (escaped_char == '"')
		return ('"');
	if (escaped_char == '\'')
		return ('\'');
	if (escaped_char == ' ')
		return (' ');
	else
		return (0);
}

char is_escape(char escaped_char, char quote)
{
	if (quote == '"')
		return (escaped_char == '\\' || escaped_char == '"');
	else
		return (escaped_char == '\\');
}

bool add_double_token(char *expr, unsigned int *i, t_vec *command, t_token *current_token, t_token_type token_type)
{
	if (expr[(*i) + 1] == expr[*i])
	{
		if (!append_token(command, current_token, token_type_plain))
			return (false);
		(*i) ++;
		if (!push_char(current_token, expr[*i]))
			return (false);
		if (!push_char(current_token, expr[*i]))
			return (false);
		if (!append_token(command, current_token, token_type))
			return (false);
	}
	else
	{
		if (!append_token(command, current_token, token_type_plain))
			return (false);
		if (!push_char(current_token, expr[*i]))
			return (false);
		//(*i) ++;
		if (!append_token(command, current_token, token_type))
			return (false);
	}
	return (true);
}

bool add_simple_token(char *expr, unsigned int i, t_vec *command, t_token *current_token)
{
	if (!append_token(command, current_token, token_type_plain))
		return (false);
	if (!push_char(current_token, expr[i]))
		return (false);
	if (!append_token(command, current_token, token_type_scope_delimiter))
		return (false);
	return (true);
}

bool parse_token_double_quote(char *expr, unsigned int *i, t_token *current_token, char *quote_char)
{
	if (expr[*i] == '\\' && expr[(*i) + 1])
	{
		(*i)++;
		if (is_escape(expr[*i], *quote_char))
		{
			char escaped_char = get_escape(expr[*i]);
			if (!push_char(current_token, escaped_char))
				return (false);
		}
		else
		{
			if (!push_char(current_token, '\\'))
				return (false);
			if (!push_char(current_token, expr[*i]))
				return (false);
		}
	}
	else if (expr[*i] == '"')
		(*quote_char) = 0;
	else
		if (!push_char(current_token, expr[*i]))
			return (false);
	return (true);
}

bool parse_token_simple_quote(char *expr, unsigned int *i, t_token *current_token, char *quote_char)
{
	if (expr[*i] == '\\' && expr[(*i) + 1])
	{
		(*i)++;
		if (is_escape(expr[*i], *quote_char))
		{
			char escaped_char = get_escape(expr[*i]);
			push_char(current_token, escaped_char);
		}
		else
		{
			push_char(current_token, '\\');
			push_char(current_token, expr[*i]);
		}
	}
	else if (expr[*i] == '\'')
		quote_char = 0;
	else
		push_char(current_token, expr[*i]);
	return (true);
}

t_tokeniser_error tokenise(char *expr, t_vec *command)
{
	vec_init(command, sizeof(t_token), 4);
	unsigned int i = 0;
	char quote_char = 0;
	bool in_parenthese = false; 
	t_token current_token;
	current_token.type = token_type_void;
	while (expr[i])
	{
		if (quote_char == '"')
			parse_token_double_quote(expr, &i, &current_token, &quote_char);
		else if (quote_char == '\'')
			parse_token_simple_quote(expr, &i, &current_token, &quote_char);
		else
		{
			if (expr[i] == '\\' && expr[i + 1])
				push_char(&current_token, expr[++i]);
			else if (expr[i] == '"')
			{
				push_char(&current_token, 0);
				quote_char = '"';
			}
			else if (expr[i] == '\'')
			{
				push_char(&current_token, 0);
				quote_char = '\'';
			}
			else if (expr[i] == '(' || expr[i] == ')' || expr[i] == ';')
				add_simple_token(expr, i, command, &current_token);
			else if (expr[i] == '&' || expr[i] == '|')
				add_double_token(expr, &i, command, &current_token, token_type_scope_delimiter);
			else if (expr[i] == '>' || expr[i] == '<')
				add_double_token(expr, &i, command, &current_token, token_type_command_delimiter);
			else if (expr[i] == ' ')
				append_token(command, &current_token, token_type_plain);
			else
				push_char(&current_token, expr[i]);
		}
		i++;
	}
	if (current_token.type != token_type_void)
		vec_append(command, &current_token);
	if (quote_char != 0)
		return (tokeniser_error_unterminated_quoted_string);
	return (tokeniser_error_succes);
}
