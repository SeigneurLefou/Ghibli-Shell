/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:25:49 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/13 15:01:24 by lchamard         ###   ########.fr       */
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

char	*expand_variable(char *raw_line, char *pre_line, size_t *i)
{
	char	*var_name;
	char	*var_content;
	char	*new_line;
	size_t	k;

	(*i)++;
	k = 0;
	var_name = NULL;
	while (raw_line[*i] && ft_isalnum(raw_line[*i]))
	{
		var_name = str_append_char(var_name, raw_line[*i]);
		(*i)++;
	}
	var_content = getenv(var_name);
	free(var_name);
	while (var_content && var_content[k])
	{
		pre_line = str_append_char(pre_line, var_content[k]);
		k++;
	}
	return (pre_line);
}

char	*expand_line(char *raw_line)
{
	char	*new_line;
	size_t	i;

	new_line = NULL;
	i = 0;
	while (raw_line && raw_line[i] && raw_line[i] != '\"')
	{
		if (raw_line[i] == '$')
			new_line = expand_variable(raw_line, new_line, &i);
		else
		{
			new_line = str_append_char(new_line, raw_line[i]);
			i++;
		}
	}
	return (new_line);
}
