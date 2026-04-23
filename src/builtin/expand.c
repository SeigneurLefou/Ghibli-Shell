/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:25:49 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/22 10:11:36 by lchamard         ###   ########.fr       */
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

char	*give_variable_content(char *raw_line, size_t *i, t_minishell *minishell)
{
	char	*var_name;
	char	*var_content;

	var_name = NULL;
	while (raw_line[*i] && ft_isalnum(raw_line[*i]))
	{
		var_name = str_append_char(var_name, raw_line[*i]);
		(*i)++;
	}
	var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
			var_name));
	free(var_name);
	return (var_content);
}

char	*expand_line(t_minishell *minishell, char *raw_line)
{
	char	*new_line;
	char	*var_content;
	size_t	i;

	new_line = NULL;
	i = 0;
	while (raw_line && raw_line[i] && raw_line[i] != '\"')
	{
		if (raw_line[i] == '$')
		{
			i++;
			var_content = give_variable_content(raw_line, &i, minishell);
			if (new_line)
				new_line = ft_strjoin(new_line, var_content);
			else
				new_line = ft_strdup(var_content);
		}
		else
		{
			new_line = str_append_char(new_line, raw_line[i]);
			i++;
		}
	}
	return (new_line);
}
