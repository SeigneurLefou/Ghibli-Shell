/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_file_queries.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:01:06 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 15:07:08 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expands.h"
#include <dirent.h>

bool	file_matches_filter(t_vec *filter, char *name)
{
	char			*wildcard;
	char			*str_filter;
	unsigned int	check_start;

	if (name[0] == '.' && *(char *)vec_get(filter, 0) != '.')
		return (false);
	str_filter = vec_to_cstring(filter);
	if (!str_filter)
		return (false);
	wildcard = ft_strchr(str_filter, '*');
	if (ft_strncmp(str_filter, name, wildcard - str_filter))
	{
		mem_free(str_filter);
		return (false);
	}
	if (ft_strlen(name) < ft_strlen(wildcard + 1))
		return (false);
	check_start = get_check_start(name, wildcard, str_filter);
	if (ft_strcmp(wildcard + 1, name + check_start))
	{
		mem_free(str_filter);
		return (false);
	}
	mem_free(str_filter);
	return (true);
}

static bool	add_file_on_match(char *name, t_vec *out)
{
	t_vec	vec_file_path;

	vec_file_path = vec_from_str(name);
	if (!vec_file_path.failed)
		vec_append(out, &vec_file_path);
	return (true);
}

bool	query_files_in_dir(t_vec *out, char *path, t_vec *filter)
{
	DIR				*dir;
	struct dirent	*dir_entry;
	bool			found;

	dir = opendir(path);
	if (!dir)
		return (false);
	dir_entry = readdir(dir);
	found = false;
	while (dir_entry)
	{
		if (file_matches_filter(filter, dir_entry->d_name))
		{
			if (!add_file_on_match(dir_entry->d_name, out))
			{
				closedir(dir);
				return (false);
			}
			found = true;
		}
		dir_entry = readdir(dir);
	}
	closedir(dir);
	return (!out->failed && found);
}

static bool	is_a_wildcard(t_token *token)
{
	t_expand_data	*expand_data;

	if (token->expandable_scopes.size != 2)
		return (false);
	expand_data = (t_expand_data *)vec_get(&token->expandable_scopes, 0);
	return (*(char *)vec_get(&token->data, expand_data->index) == '*');
}

bool	handle_wildcard(t_vec *argv, t_token *token, t_minishell *minishell)
{
	char	*path;

	if (is_a_wildcard(token))
	{
		path = env_variables_get(&minishell->env_variables_manager, "PWD");
		if (path)
			if (query_files_in_dir(argv, path, &token->data))
				return (true);
	}
	return (false);
}
