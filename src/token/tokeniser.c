/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:28:21 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/19 13:20:24 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void append_token(t_vec *command, t_token *token, t_token_type type)
{
	if (token->type != token_type_void)
	{
		token->type = type;
		vec_append(command, token);
	}
	token->type = token_type_void;
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
		vec_append(&token->data, &c);
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
		{
			if (expr[i] == '\\' && expr[i + 1])
			{
				i++;
				if (is_escape(expr[i], quote_char))
				{
					char escaped_char = get_escape(expr[i]);
					push_char(&current_token, escaped_char);
				}
				else
				{
					push_char(&current_token, '\\');
					push_char(&current_token, expr[i]);
				}
			}
			else if (expr[i] == '"')
				quote_char = 0;
			else
				push_char(&current_token, expr[i]);
		}
		else if (quote_char == '\'')
		{
			if (expr[i] == '\\' && expr[i + 1])
			{
				i++;
				if (is_escape(expr[i], quote_char))
				{
					char escaped_char = get_escape(expr[i]);
					push_char(&current_token, escaped_char);
				}
				else
				{
					push_char(&current_token, '\\');
					push_char(&current_token, expr[i]);
				}
			}
			else if (expr[i] == '\'')
				quote_char = 0;
			else
				push_char(&current_token, expr[i]);
		}
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
			else if (expr[i] == '(')
			{
				append_token(command, &current_token, token_type_plain);
				push_char(&current_token, '(');
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == ')')
			{
				append_token(command, &current_token, token_type_plain);
				push_char(&current_token, ')');
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == ';')
			{
				append_token(command, &current_token, token_type_plain);
				push_char(&current_token, ';');
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == '|')
			{
				if (expr[i + 1] == '|')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					push_char(&current_token, '|');
					push_char(&current_token, '|');
					append_token(command, &current_token, token_type_scope_delimiter);
				}
				else
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					push_char(&current_token, '|');
					append_token(command, &current_token, token_type_command_delimiter);
				}
			}
			else if (expr[i] == '&')
			{
				if (expr[i + 1] == '&')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					push_char(&current_token, '&');
					push_char(&current_token, '&');
					append_token(command, &current_token, token_type_scope_delimiter);
				}
				else
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					push_char(&current_token, '&');
					append_token(command, &current_token, token_type_command_delimiter);
				}
			}
			else if (expr[i] == '<')
			{
				if (expr[i + 1] == '<')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					push_char(&current_token, '<');
					push_char(&current_token, '<');
					append_token(command, &current_token, token_type_command_delimiter);
				}
				else
					{
					append_token(command, &current_token, token_type_plain);
					i ++;
					push_char(&current_token, '<');
					append_token(command, &current_token, token_type_command_delimiter);
				}
			}
			else if (expr[i] == '>')
			{
				if (expr[i + 1] == '>')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					push_char(&current_token, '>');
					push_char(&current_token, '>');
					append_token(command, &current_token, token_type_command_delimiter);
				}
				else
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					push_char(&current_token, '>');
					append_token(command, &current_token, token_type_command_delimiter);
				}
			}
			else if (expr[i] == ' ')
			{
				append_token(command, &current_token, token_type_plain);
			}
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
