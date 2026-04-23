/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:25:49 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/23 12:59:55 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*str_append_char(char *str, char c)
{
	size_t	i;
	char	*new_str;

	i = 0;
	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	return (new_str);
}

char	*give_variable_content(t_token *raw_line, size_t *i,
		t_minishell *minishell, size_t expand_pointer)
{
	char	*var_name;
	char	*var_content;

	var_name = NULL;
	if (*(char *)vec_get(&raw_line->data, *i) == '~')
	{
		(*i)++;
		var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
				"HOME"));
		return (var_content);
	}
	(*i)++;
	while (*i < raw_line->data.size
		&& *i <= *(size_t *)vec_get(&raw_line->expandable_scopes, expand_pointer))
	{
		var_name = str_append_char(var_name, *(char *)vec_get(&raw_line->data, *i));
		(*i)++;
	}
	var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
			var_name));
	free(var_name);
	return (var_content);
}

char	*expand_line(t_token *raw_line, t_minishell *minishell)
{
	char	*new_line;
	char	*var_content;
	size_t	i;
	size_t	expand_pointer;

	new_line = NULL;
	i = 0;
	expand_pointer = 0;
	while (i < raw_line->data.size)
	{
		if (expand_pointer < raw_line->expandable_scopes.size
			&& i == *(unsigned int *)vec_get(&raw_line->expandable_scopes, expand_pointer))
		{
			expand_pointer++;
			var_content = give_variable_content(raw_line, &i, minishell, expand_pointer);
			if (new_line)
				new_line = ft_strjoin(new_line, var_content);
			else
				new_line = ft_strdup(var_content);
		}
		else
		{
			new_line = str_append_char(new_line, *(char *)vec_get(&raw_line->data, i));
			printf("line when classical char : %s, %u\n", new_line, raw_line->expandable_scopes.size);
			i++;
		}
	}
	return (new_line);
}
