/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 06:45:58 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/26 13:49:26 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

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
	if (!key)
		return (NULL);
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

bool	expand_split(t_vec *argv, t_vec *expanded_token, char *var_content,
		bool *can_skip_token)
{
	t_vec	var_split;
	size_t	j;
	bool	split_at_end;

	if (!var_content)
		return (true);
	vec_init(&var_split, sizeof(t_vec), 5);
	vec_split_space(&var_split, var_content);
	if (!var_split.size || var_split.failed)
		return (false);
	if (!ft_isspace(var_content[0]))
		vec_expand(expanded_token, vec_get(&var_split, 0));
	split_at_end = ft_isspace(var_content[ft_strlen(var_content) - 1]);
	*can_skip_token = split_at_end;
	if (var_split.size > 1)
	{
		if (!ft_isspace(var_content[0]))
			vec_append(argv, expanded_token);
		vec_init(expanded_token, sizeof(char), 20);
		j = !ft_isspace(var_content[0]);
		while (j < var_split.size - !split_at_end)
		{
			vec_append(argv, vec_get(&var_split, j));
			j++;
		}
		if (!split_at_end)
			vec_expand(expanded_token, vec_get(&var_split, j));
	}
	vec_free(&var_split);
	return (!var_split.failed);
}

char	*path_join(char *a, char *b)
{
	unsigned int	a_size;
	char			*path;

	a_size = ft_strlen(a);
	if (a[a_size - 1] == '/')
		path = ft_strjoin(a, b);
	else
	{
		path = ft_strjoin(a, "/");
		if (!path)
			return (false);
		path = ft_strjoin(path, b);
	}
	return (path);
}

bool	file_matches_filter(t_vec *filter, char *name)
{
	char	*wildcard;
	char	*str_filter;

	if (name[0] == '.' && *(char *)vec_get(filter, 0) != '.')
		return (false);
	str_filter = vec_to_cstring(filter);
	if (!str_filter)
		return (false);
	wildcard = ft_strchr(str_filter, '*');
	if (!wildcard)
		return (false); // Shizuku has a biiiiig problem if this happens
	if (ft_strncmp(str_filter, name, wildcard - str_filter))
	{
		mem_free(str_filter);
		return (false);
	}
	if (ft_strcmp(wildcard + 1, name + ft_strlen(name) - ft_strlen(wildcard
				+ 1)))
	{
		mem_free(str_filter);
		return (false);
	}
	mem_free(str_filter);
	return (true);
}

static bool	add_file_on_match(char *path, char *name, t_vec *out)
{
	char	*file_path;
	t_vec	vec_file_path;

	file_path = path_join(path, name);
	if (!file_path)
		return (false);
	vec_file_path = vec_from_str(file_path);
	if (!vec_file_path.failed)
		vec_append(out, &vec_file_path);
	mem_free(file_path);
	return (true);
}

#include <dirent.h>

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
			if (!add_file_on_match(path, dir_entry->d_name, out))
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

static bool	handle_wildcard(t_vec *argv, t_token *token, t_minishell *minishell)
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

bool	expand(t_vec *argv, t_token *token, t_minishell *minishell)
{
	size_t			char_index;
	t_vec			expanded_token;
	char			*var_content;
	size_t			exp_data_i;
	t_expand_data	*expand_data;
	bool			can_skip_token;

	if (handle_wildcard(argv, token, minishell))
		return (true);
	char_index = 0;
	var_content = NULL;
	vec_init(&expanded_token, sizeof(char), 48);
	exp_data_i = 0;
	token->is_expand = false;
	can_skip_token = false;
	while (char_index < token->data.size)
	{
		expand_data = vec_get(&token->expandable_scopes, exp_data_i);
		if (exp_data_i < token->expandable_scopes.size
			&& char_index == expand_data->index)
		{
			exp_data_i++;
			if (*(char *)vec_get(&token->data, expand_data->index) != '*')
			{
				expand_data = vec_get(&token->expandable_scopes, exp_data_i);
				var_content = expand_tild(token, &char_index, minishell);
				if (!var_content)
					var_content = give_variable_content(token, &char_index,
							minishell, expand_data->index);
				expand_data = vec_get(&token->expandable_scopes, exp_data_i
						- 1);
				if (!var_content && expand_data->allow_split)
				{
					mem_free(var_content);
					exp_data_i++;
					continue ;
				}
				if (expand_data->allow_split)
				{
					if (!expand_split(argv, &expanded_token, var_content,
							&can_skip_token))
						return (false);
				}
				else
					add_str_to_vec_char(&expanded_token, var_content);
				mem_free(var_content);
			}
			else
			{
				vec_append(&expanded_token, vec_get(&token->data, char_index));
				char_index++;
			}
			exp_data_i++;
		}
		else
		{
			vec_append(&expanded_token, vec_get(&token->data, char_index));
			char_index++;
		}
	}
	if (((var_content || expanded_token.size) && !can_skip_token)
		|| token->no_skip)
		vec_append(argv, &expanded_token);
	return (true);
}
