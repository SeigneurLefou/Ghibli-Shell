/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:02:23 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 15:07:06 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expands.h"

char	*give_variable_content(t_token *token, size_t *i,
		t_minishell *minishell, size_t max_i)
{
	t_vec	var_name;
	char	*var_content;
	char	*key;

	vec_init(&var_name, sizeof(char), 6);
	(*i)++;
	while (*i < token->data.size && *i <= max_i)
	{
		vec_append(&var_name, vec_get(&token->data, *i));
		(*i)++;
	}
	if (var_name.failed)
	{
		vec_free(&var_name);
		return (NULL);
	}
	key = vec_to_cstring(&var_name);
	var_content = env_variables_get(&minishell->env_variables_manager, key);
	if (!var_content)
		return (NULL);
	var_content = ft_strdup(var_content);
	mem_free(key);
	vec_free(&var_name);
	return (var_content);
}

char	*expand_tild(t_token *token, size_t *i, t_minishell *minishell)
{
	char	*var_content;

	var_content = NULL;
	if (*(char *)vec_get(&token->data, *i) == '~')
	{
		var_content = env_variables_get(&minishell->env_variables_manager,
				"HOME");
		if (var_content)
		{
			var_content = ft_strdup(var_content);
			(*i)++;
		}
	}
	return (var_content);
}
