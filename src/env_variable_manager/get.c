/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:52:17 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/01 19:52:32 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

char	*env_variables_get_raw(t_env_variables_manager *env_variable_manager,
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
		if ((int)ft_strlen(element) >= key_len && !ft_strncmp(key, element,
				key_len) && (!element[key_len] || element[key_len] == '='))
			return (element);
		index++;
	}
	return (NULL);
}

char	**env_variables_get_env(t_env_variables_manager *env_variable_manager)
{
	char			**env;
	t_iterator		it;
	unsigned int	index;

	env = mem_alloc(sizeof(char *) * (env_variable_manager->variables.size + 1),
			default_error_exit, NULL, 0b1);
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

char	*env_variables_get(t_env_variables_manager *env_variable_manager,
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
		if ((int)ft_strlen(element) >= key_len && !ft_strncmp(key, element,
				key_len) && (!element[key_len] || element[key_len] == '='))
			return (element + key_len + (element[key_len] == '='));
		index++;
	}
	return (NULL);
}
