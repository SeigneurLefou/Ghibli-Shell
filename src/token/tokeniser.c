/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:28:21 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/21 19:11:37 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	set_expand(t_token *current_token, bool state, bool allow_split)
{
	t_expand_data	expand_data;

	expand_data.index = current_token->data.size - 1;
	expand_data.allow_split = allow_split;
	if (state && current_token->is_expand)
	{
		expand_data.index--;
		vec_append(&current_token->expandable_scopes, &expand_data);
		expand_data.index++;
		vec_append(&current_token->expandable_scopes, &expand_data);
		current_token->is_expand = true;
	}
	else if (!state && current_token->is_expand)
	{
		vec_append(&current_token->expandable_scopes, &expand_data);
		current_token->is_expand = false;
	}
	else if (state && !current_token->is_expand)
	{
		vec_append(&current_token->expandable_scopes, &expand_data);
		current_token->is_expand = true;
	}
}

void	append_token(t_vec *command, t_token *token, t_token_type type)
{
	set_expand(token, false, false);
	if (token->type != token_type_void)
	{
		token->type = type;
		vec_append(command, token);
	}
	token->type = token_type_void;
}

void	push_char(t_token *token, char c)
{
	if (token->type == token_type_void)
	{
		token->type = token_type_plain;
		vec_init(&token->data, sizeof(char), 16);
		vec_init(&token->expandable_scopes, sizeof(t_expand_data), 4);
	}
	if (c)
		vec_append(&token->data, &c);
}

char	get_escape(char escaped_char)
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

char	is_escape(char escaped_char, char quote)
{
	if (quote == '"')
		return (escaped_char == '\\' || escaped_char == '"');
	else
		return (false);
}

void	add_double_token(char *expr, unsigned int *i, t_vec *command,
		t_token *current_token, t_token_type token_type)
{
	set_expand(current_token, false, false);
	if (expr[(*i) + 1] == expr[*i])
	{
		append_token(command, current_token, token_type_plain);
		(*i)++;
		push_char(current_token, expr[*i]);
		push_char(current_token, expr[*i]);
		append_token(command, current_token, token_type);
	}
	else
	{
		append_token(command, current_token, token_type_plain);
		push_char(current_token, expr[*i]);
		//(*i) ++;
		append_token(command, current_token, token_type);
	}
}

void	add_simple_token(char *expr, unsigned int i, t_vec *command,
		t_token *current_token)
{
	set_expand(current_token, false, false);
	append_token(command, current_token, token_type_plain);
	push_char(current_token, expr[i]);
	append_token(command, current_token, token_type_scope_delimiter);
}

bool	is_valid_expand_char(char c)
{
	return (ft_isalnum(c) || c == '_');
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
	else if (expr[*i] == '$' && (is_valid_expand_char(expr[(*i) + 1])
			|| expr[(*i) + 1] == '?'))
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

void	parse_token_simple_quote(char *expr, unsigned int *i,
		t_token *current_token, char *quote_char)
{
	if (expr[*i] == '\'')
		(*quote_char) = 0;
	else
		push_char(current_token, expr[*i]);
}

bool	is_tilde_escape_compatible(char c)
{
	return (c == ' ' || c == '/' || c == '\0' || c == '|' || c == '&'
		|| c == '<' || c == '>');
}

void	check_tokens_integrity(t_vec *command)
{
	unsigned int	index;
	t_token			*token;

	index = 0;
	if (command->failed)
		memory_allocation_failed_error_exit();
	while (index < command->size)
	{
		token = vec_get(command, index);
		if (token->data.failed || token->expandable_scopes.failed)
			memory_allocation_failed_error_exit();
		index++;
	}
}

t_tokeniser_error	tokenise(char *expr, t_vec *command)
{
	unsigned int	i;
	char			quote_char;
	t_token			current_token;

	vec_init(command, sizeof(t_token), 4);
	i = 0;
	quote_char = 0;
	current_token.type = token_type_void;
	current_token.is_expand = false;
	current_token.no_skip = false;
	while (expr[i])
	{
		if (quote_char == '"')
			parse_token_double_quote(expr, &i, &current_token, &quote_char);
		else if (quote_char == '\'')
			parse_token_simple_quote(expr, &i, &current_token, &quote_char);
		else
		{
			if (expr[i] == '\\' && expr[i + 1])
			{
				push_char(&current_token, expr[++i]);
				set_expand(&current_token, false, false);
			}
			else if (expr[i] == '"')
			{
				push_char(&current_token, 0);
				quote_char = '"';
				current_token.no_skip = true;
				set_expand(&current_token, false, false);
			}
			else if (expr[i] == '\'')
			{
				push_char(&current_token, 0);
				quote_char = '\'';
				current_token.no_skip = true;
				set_expand(&current_token, false, false);
			}
			else if (expr[i] == '*')
			{
				push_char(&current_token, expr[i]);
				set_expand(&current_token, true, false);
				set_expand(&current_token, false, false);
			}
			else if (expr[i] == '$' && (is_valid_expand_char(expr[i + 1])
					|| expr[i + 1] == '?'))
			{
				push_char(&current_token, expr[i]);
				set_expand(&current_token, true, true);
			}
			else if (expr[i] == '~' && current_token.type == token_type_void
				&& is_tilde_escape_compatible(expr[i + 1]))
			{
				push_char(&current_token, expr[i]);
				set_expand(&current_token, true, false);
				set_expand(&current_token, false, false);
			}
			else if (expr[i] == '(' || expr[i] == ')' || expr[i] == ';')
				add_simple_token(expr, i, command, &current_token);
			else if (expr[i] == '&' || expr[i] == '|')
				add_double_token(expr, &i, command, &current_token,
					token_type_scope_delimiter);
			else if (expr[i] == '>' || expr[i] == '<')
				add_double_token(expr, &i, command, &current_token,
					token_type_command_delimiter);
			else if (expr[i] == ' ')
				append_token(command, &current_token, token_type_plain);
			else
			{
				if (current_token.is_expand && expr[i - 1] == '?')
					set_expand(&current_token, false, false);
				else if (!is_valid_expand_char(expr[i]) && expr[i] != '?')
					set_expand(&current_token, false, false);
				push_char(&current_token, expr[i]);
			}
		}
		i++;
	}
	set_expand(&current_token, false, false);
	if (current_token.type != token_type_void)
		vec_append(command, &current_token);
	check_tokens_integrity(command);
	if (quote_char != 0)
		return (tokeniser_error_unterminated_quoted_string);
	return (tokeniser_error_succes);
}
