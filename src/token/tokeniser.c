/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:28:21 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 14:28:22 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void append_token(t_vec *command, t_token *token, t_token_type type)
{
	t_token new;

	vec_init(&new.data, sizeof(char), 16);
	token->type = type;
	if (token->data.size)
		vec_append(command, token);
	else
		vec_free(&token->data);
	*token = new;
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
	vec_init(&current_token.data, sizeof(char), 16);
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
					vec_append(&current_token.data, &escaped_char);
				}
				else
				{
					vec_append(&current_token.data, "\\");
					vec_append(&current_token.data, &expr[i]);
				}
			}
			else if (expr[i] == '"')
				quote_char = 0;
			else
				vec_append(&current_token.data, &expr[i]);
		}
		else if (quote_char == '\'')
		{
			if (expr[i] == '\\' && expr[i + 1])
			{
				i++;
				if (is_escape(expr[i], quote_char))
				{
					char escaped_char = get_escape(expr[i]);
					vec_append(&current_token.data, &escaped_char);
				}
				else
				{
					vec_append(&current_token.data, "\\");
					vec_append(&current_token.data, &expr[i]);
				}
			}
			else if (expr[i] == '\'')
				quote_char = 0;
			else
				vec_append(&current_token.data, &expr[i]);
		}
		else
		{
			if (expr[i] == '\\' && expr[i + 1])
				vec_append(&current_token.data, &expr[++i]);
			else if (expr[i] == '"')
				quote_char = '"';
			else if (expr[i] == '\'')
				quote_char = '\'';
			else if (expr[i] == '(')
			{
				append_token(command, &current_token, token_type_plain);
				vec_append(&current_token.data, &expr[i]);
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == ')')
			{
				append_token(command, &current_token, token_type_plain);
				vec_append(&current_token.data, &expr[i]);
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == ';')
			{
				append_token(command, &current_token, token_type_plain);
				vec_append(&current_token.data, &expr[i]);
				append_token(command, &current_token, token_type_scope_delimiter);
			}
			else if (expr[i] == '|')
			{
				if (expr[i + 1] == '|')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "|");
					vec_append(&current_token.data, "|");
					append_token(command, &current_token, token_type_scope_delimiter);
				}
				else
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "|");
					append_token(command, &current_token, token_type_command_delimiter);
				}
			}
			else if (expr[i] == '&')
			{
				if (expr[i + 1] == '&')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "&");
					vec_append(&current_token.data, "&");
					append_token(command, &current_token, token_type_scope_delimiter);
				}
				else
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "&");
					append_token(command, &current_token, token_type_command_delimiter);
				}
			}
			else if (expr[i] == '<')
			{
				if (expr[i + 1] == '<')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "<");
					vec_append(&current_token.data, "<");
					append_token(command, &current_token, token_type_command_delimiter);
				}
				else
					{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, "<");
					append_token(command, &current_token, token_type_command_delimiter);
				}
			}
			else if (expr[i] == '>')
			{
				if (expr[i + 1] == '>')
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, ">");
					vec_append(&current_token.data, ">");
					append_token(command, &current_token, token_type_command_delimiter);
				}
				else
				{
					append_token(command, &current_token, token_type_plain);
					i ++;
					vec_append(&current_token.data, ">");
					append_token(command, &current_token, token_type_command_delimiter);
				}
			}
			else if (expr[i] == ' ')
			{
				append_token(command, &current_token, token_type_plain);
			}
			else
				vec_append(&current_token.data, &expr[i]);
		}
		i++;
	}
	current_token.type = token_type_plain;
	vec_append(command, &current_token);
	if (quote_char != 0)
		return (tokeniser_error_unterminated_quoted_string);
	return (tokeniser_error_succes);
}
