/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 06:45:58 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/30 18:58:23 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*give_variable_content(t_token *token, size_t *i,
		t_minishell *minishell, size_t max_i)
{
	t_vec	var_name;
	char	*var_content;

	vec_init(&var_name, sizeof(char), 6);
	(*i)++;
	while (*i < token->data.size
		&& *i <= max_i)
	{
		vec_append(&var_name, vec_get(&token->data, *i));
		(*i)++;
	}
	var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
			vec_to_cstring(&var_name)));
	vec_free(&var_name);
	return (var_content);
}

char	*expand_tild(t_token *token, size_t *i, t_minishell *minishell)
{
	char	*var_content;

	var_content = NULL;
	if (*(char *)vec_get(&token->data, *i) == '~')
	{
		var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
				"HOME"));
		(*i)++;
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

bool	expand_split(t_vec *argv, t_vec *new_line, char *var_content)
{
	t_vec	var_split;
	size_t	j;
	size_t		i;

	vec_init(&var_split, sizeof(t_vec), 5);
	vec_split(&var_split, var_content, ' ');
	vec_expand(new_line, vec_get(&var_split, 0));
	if (var_split.size > 1)
	{
		vec_append(argv, new_line); // <- ICI
		printf("new_line size type : %u\n", new_line->type_size);
		printf("expand argv[%d] size of : %d, size of vec : %lu\n", 1, (*(t_vec *)vec_get(argv, 1)).type_size, sizeof(char));
		vec_free(new_line);
		vec_init(new_line, sizeof(char), 20);
		j = 1;
		while (j < var_split.size - 1)
		{
			vec_append(argv, vec_get(&var_split, j));
			printf("var_split[%lu] size of : %d, size of vec : %lu\n", j, (*(t_vec *)vec_get(&var_split, j)).type_size, sizeof(char));
			printf("expand argv[%lu] size of : %d, size of vec : %lu\n", j + 1, (*(t_vec *)vec_get(argv, j + 1)).type_size, sizeof(char));
			j++;
		}
		vec_expand(new_line, vec_get(&var_split, j));
		printf("new_line size type : %u\n", new_line->type_size);
	}
	i = 0;
	while (i < argv->size)
	{
		printf("expand argv[%lu] size of : %d, size of vec : %lu\n", i, (*(t_vec *)vec_get(argv, i)).type_size, sizeof(char));
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
			&& i == ((t_expand_data *)vec_get(&token->expandable_scopes, expand_pointer))->index)
		{
			expand_pointer++;
			var_content = expand_tild(token, &i, minishell);
			if (!var_content)
				var_content = give_variable_content(token, &i, minishell,
						(*(t_expand_data *)vec_get(&token->expandable_scopes, expand_pointer)).index);
			if (((t_expand_data *)vec_get(&token->expandable_scopes, expand_pointer - 1))->allow_split)
			{
				if (!expand_split(argv, &new_line, var_content))
					return (false);
			}
			else
				add_str_to_vec_char(&new_line, var_content);
			free(var_content);
			expand_pointer++;
		}
		else
		{
			vec_append(&new_line, vec_get(&token->data, i));
			i++;
		}
	}
	vec_append(argv, &new_line);
	return (true);
}
