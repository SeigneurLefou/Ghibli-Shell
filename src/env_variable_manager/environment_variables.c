/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:34:44 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/16 13:55:19 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_env_variables_manager	env_variables_manager_new(void)
{
	t_env_variables_manager	env_variable_manager;

	env_variable_manager.variables = list_new();
	return (env_variable_manager);
}

static char *env_variables_manager_create_line(char *key, char *value)
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
	ft_memcpy(line + key_size + 1, key, value_size);
	line[key_size] = '=';
	line[key_size + value_size + 1] = 0;
	return (line);
} 

bool	env_variables_manager_add_variable(t_env_variables_manager *env_variable_manager,
		char *key, char *value)
{
	char * line = env_variables_manager_create_line(key, value);
	list_push_back(&env_variable_manager->variables, &line);
	return (true);
}

char	**env_variables_manager_get_env_compatible_variables_char_star_star(t_env_variables_manager *env_variable_manager)
{
	char			**env;
	t_iterator		it;
	unsigned int	index;

	env = malloc(env_variable_manager->variables.size + 1);
	if (!env)
		return (NULL);
	env[env_variable_manager->variables.size] = NULL;
	iterator_new(&env_variable_manager->variables, 0);
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

	iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if (ft_strcmp(key, element) && (element)[ft_strlen(key)] == '=')
			return (element + ft_strlen(key) + 1);
	}
	return (NULL);
}

bool	env_variable_manager_set(t_env_variables_manager *env_variable_manager,
		char *key, char *value)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;

	iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if (ft_strcmp(key, element) && (element)[ft_strlen(key)] == '=')
		{
			t_list_cell * cell = list_get_cell_at_index(&env_variable_manager->variables, index);
			cell->value = env_variables_manager_create_line(key, value);
			if (!cell->value)
				return (false);
			return (true);
		}
	}
	if (!env_variables_manager_add_variable(env_variable_manager, key, value))
		return (false);
	return (true);
}

bool	env_variable_manager_unset_key(t_env_variables_manager *env_variable_manager,
		char *key)
{
	unsigned int	index;
	char			**element;
	t_iterator		it;

	iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if (ft_strcmp(key, *element) && (*element)[ft_strlen(key)] == '=')
		{
			list_pop_at_free(&env_variable_manager->variables, index, free);
			return (true);
		}
	}
	return (false);
}

void	env_variables_manager_free(t_env_variables_manager *env_variable_manager)
{
	list_clear_and_free(&env_variable_manager->variables, free);
}
