/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:58:26 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/24 17:27:23 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*give_variable_content(t_token *token, size_t *i,
		t_minishell *minishell, size_t expand_pointer)
{
	t_vec	var_name;
	char	*var_content;

	vec_init(&var_name, sizeof(char), 6);
	(*i)++;
	while (*i < token->data.size
		&& *i <= *(size_t *)vec_get(&token->expandable_scopes, expand_pointer))
	{
		vec_append(&var_name, vec_get(&token->data, *i));
		(*i)++;
	}
	var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
			vec_to_cstring(&var_name)));
	vec_free(&var_name);
	return (var_content);
}

char	*expand_tild(t_token *token, size_t *i,
		t_minishell *minishell)
{
	char	*var_content;
	
	var_content = NULL;
	if (*(char *)vec_get(&token->data, *i) == '~')
	{
		(*i)++;
		var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
				"HOME"));
	}
	return (var_content);
}
bool	add_str_to_vec_char(t_vec *new_line, char *var_content)
{
	int	i;

	i = 0;
	while (var_content[i])
	{
		if (!vec_append(new_line, &var_content[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	expand(t_vec *argv, t_token *token, t_minishell *minishell)
{
	size_t	i;
	t_vec	new_line;
	char	*var_content;
	size_t	expand_pointer;

	i = 0;
	vec_init(&new_line, sizeof(char), 20);
	expand_pointer = 0;
	while (i < token->data.size)
	{
		if (expand_pointer < token->expandable_scopes.size
			&& i == *(unsigned int *)vec_get(&token->expandable_scopes, expand_pointer))
		{
			expand_pointer++;
			var_content = expand_tild(token, &i, minishell);
			if (!var_content)
				var_content = give_variable_content(token, &i, minishell, expand_pointer);
			add_str_to_vec_char(&new_line, var_content);
			free(var_content);
		}
		else
			vec_append(&new_line, vec_get(&token->data, i));
		i++;
	}
	vec_append(argv, &new_line); // TODO : expand the last argv with new_line
	return (true);
}
