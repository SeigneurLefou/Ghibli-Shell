/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 06:45:58 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/13 18:51:15 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
	free(key);
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

bool	add_str_to_vec_char(t_vec *new_line, char *var_content)
{
	int	i;

	if (!var_content)
		return (true);
	i = 0;
	while (var_content[i])
	{
		vec_append(new_line, &var_content[i]);
		i++;
	}
	return (!new_line->failed);
}

bool	expand_split(t_vec *argv, t_vec *new_line, char *var_content)
{
	t_vec	var_split;
	size_t	j;

	if (!var_content)
		return (true);
	vec_init(&var_split, sizeof(t_vec), 5);
	vec_split(&var_split, var_content, ' ');
	vec_expand(new_line, vec_get(&var_split, 0));
	if (var_split.size > 1)
	{
		vec_append(argv, new_line);
		vec_init(new_line, sizeof(char), 20);
		j = 1;
		while (j < var_split.size - 1)
		{
			vec_append(argv, vec_get(&var_split, j));
			j++;
		}
		vec_expand(new_line, vec_get(&var_split, j));
	}
	vec_free(&var_split);
	return (!var_split.failed);
}

char *path_join(char *a, char *b)
{
	unsigned int a_size;
	char *path;

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

struct s_parsed_file_name
{
	char *file_name;
	char *extension;
	bool match_all;
};

struct s_parsed_file_name parse_file_name(char *name)
{
	char *dot;
	struct s_parsed_file_name parsed;
	
	ft_bzero(&parsed, sizeof(struct s_parsed_file_name));
	parsed.match_all = !ft_strcmp(name, "*");
	if (parsed.match_all)
		return (parsed);
	dot = ft_strchr(name, '.');
	if (!dot)
	{
		parsed.file_name = ft_strdup(name);
		return (parsed);
	}
	parsed.extension = ft_strdup(dot + 1);
	if (!parsed.extension)
		return (parsed);
	parsed.file_name = malloc(dot - name + 1);
	if (!parsed.file_name)
	{
		free(parsed.extension);
		parsed.extension = NULL;
		return (parsed);
	}
	parsed.file_name[dot - name] = 0;
	ft_memcpy(parsed.file_name, name, dot - name);
	return (parsed);
}


void free_parsed_file_name(struct s_parsed_file_name parsed)
{
	free(parsed.extension);
	free(parsed.file_name);
}

bool	file_matches_filter(struct s_parsed_file_name filter, char *name)
{
	struct s_parsed_file_name parsed;
	bool file_name_match;
	bool extension_match;
	
	file_name_match = false;
	extension_match = false;
	if (filter.match_all)
		return (true);
	parsed = parse_file_name(name);
	if (parsed.file_name == filter.file_name || (!ft_strcmp(filter.file_name, "*") || !ft_strcmp(filter.file_name, parsed.file_name)))
		file_name_match = true;
	if (parsed.extension == filter.extension || (!ft_strcmp(filter.extension, "*") || !ft_strcmp(filter.extension, parsed.extension)))
		extension_match = true;
	free_parsed_file_name(parsed);
	return (file_name_match && extension_match);
}

#include <dirent.h>
bool	query_files_in_dir(t_vec *files, char *path, char *filter)
{
	DIR *dir;
	struct dirent *dir_entry;
	char *file_path;
	struct s_parsed_file_name parsed_filter;

	parsed_filter = parse_file_name(filter);
	dir = opendir(path);
	if (!dir)
		return (false);
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		if (file_matches_filter(parsed_filter, dir_entry->d_name))
		{
			file_path = path_join(path, dir_entry->d_name);
			if (!file_path)
				{
					return (false);
					closedir(dir);
				}
			vec_append(files, file_path);
		}
		dir_entry = readdir(dir);
	}
	closedir(dir);
	return (!files->failed);
}

bool	expand(t_vec *argv, t_token *token, t_minishell *minishell)
{
	size_t			i;
	t_vec			new_line;
	char			*var_content;
	size_t			expand_pointer;
	t_expand_data	*expand_data;

	i = 0;
	var_content = NULL;
	vec_init(&new_line, sizeof(char), 20);
	expand_pointer = 0;
	while (i < token->data.size)
	{
		if (expand_pointer < token->expandable_scopes.size
			&& i == ((t_expand_data *)vec_get(&token->expandable_scopes,
					expand_pointer))->index)
		{
			expand_pointer++;
			var_content = expand_tild(token, &i, minishell);
			expand_data = vec_get(&token->expandable_scopes, expand_pointer);
			if (!var_content)
				var_content = give_variable_content(token, &i, minishell,
						expand_data->index);
			expand_data = vec_get(&token->expandable_scopes, expand_pointer
					- 1);
			if (!var_content && expand_data->allow_split)
			{
				free(var_content);
				expand_pointer++;
				continue ;
			}
			if (expand_data->allow_split)
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
	if (var_content || new_line.size)
		vec_append(argv, &new_line);
	return (true);
}
