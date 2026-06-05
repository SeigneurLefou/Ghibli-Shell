/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 06:45:58 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/05 15:07:10 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expands.h"
#include "utils.h"

bool	setup_expander(struct s_expander_data *exp_data, t_vec *argv,
		t_token *token, t_minishell *minishell)
{
	if (handle_wildcard(argv, token, minishell))
		return (false);
	exp_data->char_index = 0;
	exp_data->var_content = NULL;
	vec_init(&exp_data->expanded_token, sizeof(char), 48);
	exp_data->exp_data_i = 0;
	token->is_expand = false;
	exp_data->skip_token = false;
	return (true);
}

void	add_remaining_token(struct s_expander_data *exp_data, t_vec *argv,
		t_token *token)
{
	if (((exp_data->var_content || exp_data->expanded_token.size)
			&& !exp_data->skip_token) || token->no_skip)
		vec_append(argv, &exp_data->expanded_token);
}

bool	expand(t_vec *argv, t_token *token, t_minishell *minishell)
{
	struct s_expander_data	exp_data;

	if (!setup_expander(&exp_data, argv, token, minishell))
		return (true);
	while (exp_data.char_index < token->data.size)
	{
		exp_data.expand_data = vec_get(&token->expandable_scopes,
				exp_data.exp_data_i);
		if (exp_data.exp_data_i < token->expandable_scopes.size
			&& exp_data.char_index == exp_data.expand_data->index)
		{
			if (!expand_variable(&exp_data, argv, minishell, token))
				return (false);
			exp_data.exp_data_i++;
		}
		else
		{
			exp_data.skip_token = false;
			vec_append(&exp_data.expanded_token, vec_get(&token->data,
					exp_data.char_index++));
		}
	}
	add_remaining_token(&exp_data, argv, token);
	return (true);
}
