/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:34:44 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/01 19:52:10 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

bool	env_variables_exists(t_env_variables_manager *env_variable_manager,
		char *key)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;
	int				key_len;

	key_len = ft_strlen(key);
	it = iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if (!ft_strncmp(key, element, key_len) && (!element[key_len]
				|| element[key_len] == '='))
			return (true);
		index++;
	}
	return (false);
}

bool	env_variables_unset_key(t_env_variables_manager *env_variable_manager,
		char *key)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;
	int				key_len;

	key_len = ft_strlen(key);
	it = iterator_new(&env_variable_manager->variables, 0);
	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = iterator_next(&it);
		if (!ft_strncmp(key, element, key_len) && (!element[key_len]
				|| element[key_len] == '='))
		{
			list_pop_at_free(&env_variable_manager->variables, index, mem_free);
			return (true);
		}
		index++;
	}
	return (false);
}

void	env_variables_free(t_env_variables_manager *env_variable_manager)
{
	list_clear(&env_variable_manager->variables, mem_free);
}

void	env_variables_add_from_env(t_env_variables_manager *env_var_manager,
		char **env)
{
	unsigned int	index;

	index = 0;
	while (env[index])
	{
		if (!env_variables_set_raw(env_var_manager, env[index]))
		{
			memory_allocation_failed_error_exit();
		}
		index++;
	}
}
