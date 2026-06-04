/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 06:45:58 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/04 19:57:55 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include <dirent.h>

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
bool	setup_expand_split(char *var_content, t_vec *var_split,
		t_vec *expanded_token)
{
	vec_init(var_split, sizeof(t_vec), 5);
	vec_split_space(var_split, var_content);
	if (!var_split->size)
		return (false);
	if (!ft_isspace(var_content[0]))
		vec_expand(expanded_token, vec_get(var_split, 0));
	return (true);
}

bool	expand_split(t_vec *argv, t_vec *expanded_token, char *var_content,
		bool *can_skip_token)
{
	t_vec	var_split;
	size_t	j;
	bool	split_at_end;

	if (!var_content)
		return (true);
	if (!setup_expand_split(var_content, &var_split, expanded_token))
		return (false);
	split_at_end = ft_isspace(var_content[ft_strlen(var_content) - 1]);
	*can_skip_token = split_at_end;
	if (var_split.size > 1)
	{
		if (expanded_token->size)
			vec_append(argv, expanded_token);
		vec_init(expanded_token, sizeof(char), 20);
		j = !ft_isspace(var_content[0]);
		while (j < var_split.size - !split_at_end)
			vec_append(argv, vec_get(&var_split, j++));
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

static unsigned int	get_check_start(char *name, char *wildcard,
		char *str_filter)
{
	unsigned int	check_start;

	check_start = ft_strlen(name) - ft_strlen(wildcard + 1);
	if (check_start < wildcard - str_filter)
		check_start = wildcard - str_filter;
	return (check_start);
}

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

struct				s_expander_data
{
	t_token			*token;
	t_expand_data	*expand_data;
	char			*var_content;
	size_t			exp_data_i;
	size_t			char_index;
	bool			skip_token;
	t_vec			expanded_token;
};

bool	expand_variable(struct s_expander_data *data, t_vec *argv,
		t_minishell *minishell, t_token *token)
{
	data->exp_data_i++;
	if (*(char *)vec_get(&token->data, data->expand_data->index) != '*')
	{
		data->expand_data = vec_get(&token->expandable_scopes,
				data->exp_data_i);
		data->var_content = expand_tild(token, &data->char_index, minishell);
		if (!data->var_content)
			data->var_content = give_variable_content(token, &data->char_index,
					minishell, data->expand_data->index);
		data->expand_data = vec_get(&token->expandable_scopes, data->exp_data_i
				- 1);
		if (!data->var_content && data->expand_data->allow_split)
			return (true);
		else if (data->expand_data->allow_split && !expand_split(argv,
				&data->expanded_token, data->var_content, &data->skip_token))
			return (false);
		else if (!data->expand_data->allow_split)
			add_str_to_vec_char(&data->expanded_token, data->var_content);
		mem_free(data->var_content);
	}
	else
		vec_append(&data->expanded_token, vec_get(&token->data,
				data->char_index++));
	return (true);
}

bool	setup_expander(struct s_expander_data *exp_data, t_vec *argv,
		t_token *token, t_minishell *minishell)
{
	if (handle_wildcard(argv, token, minishell))
		return (false);
	exp_data->char_index = 0;
	exp_data->var_content = NULL;
	vec_init(&exp_data->expanded_token, sizeof(char), 48);
	exp_data->exp_data_i = 0;
	token->is_expand = false;
	exp_data->skip_token = false;
	return (true);
}

bool	expand(t_vec *argv, t_token *token, t_minishell *minishell)
{
	struct s_expander_data	exp_data;

	if (!setup_expander(&exp_data, argv, token, minishell))
		return (true);
	while (exp_data.char_index < token->data.size)
	{
		exp_data.expand_data = vec_get(&token->expandable_scopes,
				exp_data.exp_data_i);
		if (exp_data.exp_data_i < token->expandable_scopes.size
			&& exp_data.char_index == exp_data.expand_data->index)
		{
			if (!expand_variable(&exp_data, argv, minishell, token))
				return (false);
			exp_data.exp_data_i++;
		}
		else
			vec_append(&exp_data.expanded_token, vec_get(&token->data,
					exp_data.char_index++));
	}
	if (((exp_data.var_content || exp_data.expanded_token.size)
			&& !exp_data.skip_token) || token->no_skip)
		vec_append(argv, &exp_data.expanded_token);
	return (true);
}
