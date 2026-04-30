/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .expand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:25:49 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/24 14:21:04 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	add_var_content_to_line_vector(t_vec *line, char *var_content,
			bool is_split)
{
	t_vec	splited_var_content;
	char	*new_line;

	if (!is_split)
	{
		new_line = vec_get(line, 0);
		if (new_line)
			new_line = ft_strjoin(new_line, var_content);
		else
			new_line = ft_strdup(var_content);
	}
	else
	{
		vec_init(&splited_var_content, sizeof(char *), 5);
		vec_split(&splited_var_content, var_content, ' ');
		printf("first el var_content : %s\n", *(char **)vec_get(&splited_var_content, 0));
		vec_expand_and_free(line, &splited_var_content); // TODO : le premier element du var content doit etre join avec le dernier de line puis le reste est expand
		
	}
}

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

char	**expand_line(t_token *raw_line, t_minishell *minishell)
{
	char	*new_line;
	char	*var_content;
	size_t	i;
	size_t	expand_pointer;
	char	**array_line;
	t_vec	res;

	vec_init(&res, sizeof(t_vec), 5);
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
			add_var_content_to_line_vector(&res, var_content, is_split);
		}
		else
		{
			new_line = str_append_char(new_line, *(char *)vec_get(&raw_line->data, i));
			i++;
			printf("new_line : %s\n", new_line);
		}
	}
	array_line = vec_to_charss(&res);
	return (array_line);
}
