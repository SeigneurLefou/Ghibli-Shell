/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:45:18 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 14:02:42 by yben-dje         ###   ########.fr       */
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

void	push_simple_char(char *expr, unsigned int *i, t_token *current_token)
{
	if (current_token->is_expand && expr[*i - 1] == '?')
		set_expand(current_token, false, false);
	else if (!is_valid_expand_char(expr[*i]) && expr[*i] != '?')
		set_expand(current_token, false, false);
	push_char(current_token, expr[*i]);
}
