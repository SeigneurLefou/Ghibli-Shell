/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:33:58 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 16:34:32 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_variable_content(char *start, t_minishell *minishell)
{
	char			*name;
	unsigned int	index;
	char			*value;
	unsigned int	size;

	size = get_variable_name_len(start);
	name = mem_alloc(size + 1, default_error_exit, NULL, 0b1);
	name[size] = 0;
	index = 0;
	while (index < size)
	{
		name[index] = start[index];
		index++;
	}
	value = env_variables_get(&minishell->env_variables_manager, name);
	return (value);
}

static void	add_expand(unsigned int *index, char *line, t_vec *expanded,
		t_minishell *minishell)
{
	char	*data;

	(*index)++;
	data = get_variable_content(line + (*index), minishell);
	if (data)
		vec_expand_from_str(expanded, data);
	(*index) += get_variable_name_len(line + (*index));
}

char	*expand_str(char *line, t_minishell *minishell)
{
	t_vec			expanded;
	unsigned int	index;
	unsigned int	line_size;
	char			*data;

	line_size = ft_strlen(line);
	vec_init(&expanded, sizeof(char), 10);
	index = 0;
	while (index < line_size)
	{
		if (line[index] == '\\' && line[index + 1] == '$')
		{
			vec_append(&expanded, "$");
			index += 2;
		}
		else if (line[index] == '$' && is_valid_expand_char(line[index + 1]))
			add_expand(&index, line, &expanded, minishell);
		else
			vec_append(&expanded, &line[index++]);
	}
	data = vec_to_cstring(&expanded);
	vec_free(&expanded);
	return (data);
}
