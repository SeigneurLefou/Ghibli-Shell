/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:34:44 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/21 18:23:28 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_env_variables_manager	env_variables_manager_new(void)
{
	t_env_variables_manager	env_variable_manager;

	env_variable_manager.variables = list_new();
	return (env_variable_manager);
}

bool	env_variables_manager_set_raw_line(t_env_variables_manager *env_variable_manager,
		char *line)
{
	char	*new;
	
	char *key = ft_substr(line, 0, ft_strrchr(line, '=') - line);
	if (env_variable_manager_exists(env_variable_manager, key))
		env_variable_manager_unset_key(env_variable_manager, key);
	new = ft_strdup(line);
	if (!line)
		return (false);
	if (!list_push_back(&env_variable_manager->variables, new))
		return (false);
	return (true);
}

static char	*env_variables_manager_create_line(char *key, char *value)
{
	char			*line;
	unsigned int	key_size;
	unsigned int	value_size;

	key_size = ft_strlen(key);
	value_size = ft_strlen(value);
	line = malloc(key_size + value_size + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, key, key_size);
	ft_memcpy(line + key_size + 1, value, value_size);
	line[key_size] = '=';
	line[key_size + value_size + 1] = 0;
	return (line);
}

bool	env_variables_manager_add_variable(t_env_variables_manager *env_variable_manager,
		char *key, char *value)
{
	char	*line;

	line = env_variables_manager_create_line(key, value);
	list_push_back(&env_variable_manager->variables, &line);
	return (true);
}

char	**env_variables_manager_get_env_compatible_variables_char_star_star(t_env_variables_manager *env_variable_manager)
{
	char			**env;
	t_iterator		it;
	unsigned int	index;

	env = malloc(sizeof(char *) * (env_variable_manager->variables.size + 1));
	if (!env)
		return (NULL);
	env[env_variable_manager->variables.size] = NULL;
	it = iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		env[index] = iterator_next(&it);
		index++;
	}
	return (env);
}

char	*env_variable_manager_get_single(t_env_variables_manager *env_variable_manager,
		char *key)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;

	int key_len = ft_strlen(key);
	it = iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if ((int)ft_strlen(element) >= key_len && !ft_strncmp(key, element, key_len) && (!element[key_len] || element[key_len] == '='))
			return (element + key_len + (element[key_len] == '='));
		index++;
	}
	return (NULL);
}

bool env_variable_manager_exists(t_env_variables_manager *env_variable_manager,
		char *key)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;

	int key_len = ft_strlen(key);
	it = iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if (!ft_strncmp(key, element, key_len) && (!element[key_len] || element[key_len] == '='))
			return (true);
		index++;
	}
	return (false);
}

bool	env_variable_manager_set(t_env_variables_manager *env_variable_manager,
		char *key, char *value)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;
	t_list_cell		*cell;
	
	int key_len = ft_strlen(key);
	it = iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if (!ft_strncmp(key, element, key_len) && element[key_len] == '=')
		{
			cell = list_get_cell_at_index(&env_variable_manager->variables,
					index);
			free(cell->value);
			cell->value = env_variables_manager_create_line(key, value);
			if (!cell->value)
				return (false);
			return (true);
		}
		index++;
	}
	if (!env_variables_manager_add_variable(env_variable_manager, key, value))
		return (false);
	return (true);
}

bool	env_variable_manager_unset_key(t_env_variables_manager *env_variable_manager,
		char *key)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;

	int key_len = ft_strlen(key);
	it = iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if (!ft_strncmp(key, element, key_len) && element[key_len] == '=')
		{
			list_pop_at_free(&env_variable_manager->variables, index, free);
			return (true);
		}
		index++;
	}
	return (false);
}

void	env_variables_manager_free(t_env_variables_manager *env_variable_manager)
{
	list_clear(&env_variable_manager->variables, free);
}

bool	env_variables_manager_add_variables_from_env(t_env_variables_manager *env_variable_manager, char **env)
{
	unsigned int index;

	index = 0;
	while (env[index])
	{
		if (!env_variables_manager_set_raw_line(env_variable_manager, env[index]))
		{
			env_variables_manager_free(env_variable_manager);
			return (false);
		}
		index++;
	}
	return (true);
}
