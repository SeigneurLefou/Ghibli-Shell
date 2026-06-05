/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:04:00 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 15:07:09 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expands.h"

bool	add_str_to_vec_char(t_vec *expanded_token, char *var_content)
{
	int	i;

	if (!var_content)
		return (true);
	i = 0;
	while (var_content[i])
	{
		vec_append(expanded_token, &var_content[i]);
		i++;
	}
	return (!expanded_token->failed);
}

unsigned int	get_check_start(char *name, char *wildcard, char *str_filter)
{
	unsigned int	check_start;

	check_start = ft_strlen(name) - ft_strlen(wildcard + 1);
	if (check_start < wildcard - str_filter)
		check_start = wildcard - str_filter;
	return (check_start);
}

bool	expand_variable(struct s_expander_data *data, t_vec *argv,
		t_minishell *minishell, t_token *token)
{
	data->exp_data_i++;
	if (*(char *)vec_get(&token->data, data->expand_data->index) != '*')
	{
		data->expand_data = vec_get(&token->expandable_scopes,
				data->exp_data_i);
		data->var_content = expand_tild(token, &data->char_index, minishell);
		if (!data->var_content)
			data->var_content = give_variable_content(token, &data->char_index,
					minishell, data->expand_data->index);
		data->expand_data = vec_get(&token->expandable_scopes, data->exp_data_i
				- 1);
		if (!data->var_content && data->expand_data->allow_split)
			return (true);
		else if (data->expand_data->allow_split && !expand_split(argv,
				&data->expanded_token, data->var_content, &data->skip_token))
			return (false);
		else if (!data->expand_data->allow_split)
			add_str_to_vec_char(&data->expanded_token, data->var_content);
		mem_free(data->var_content);
	}
	else
		vec_append(&data->expanded_token, vec_get(&token->data,
				data->char_index++));
	return (true);
}
