/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:34:44 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/13 17:56:08 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vec.h"

typedef struct s_env_variables_manager
{
	t_vec				variables;
}						t_env_variables_manager;

t_env_variables_manager	env_variables_manager_new(void)
{
	t_env_variables_manager	env_variable_manager;

	vec_init(&env_variable_manager.variables, sizeof(char **), 4);
	return (env_variable_manager);
}

bool	env_variables_manager_add_variable(t_env_variables_manager *env_variable_manager,
		char *key, char *value)
{
	char			*line;
	unsigned int	key_size;
	unsigned int	value_size;

	key_size = ft_strlen(key);
	value_size = ft_strlen(value);
	line = malloc(key_size + value_size + 2);
	if (!line)
		return (false);
	ft_memcpy(line, key, key_size);
	ft_memcpy(line + key_size + 1, key, value_size);
	line[key_size] = '=';
	line[key_size + value_size + 1] = 0;
	vec_append(&env_variable_manager->variables, &line);
    return (true);
}

char	**env_variables_manager_get_env_compatible_variables(t_env_variables_manager *env_variable_manager)
{
	char			**env;

	env = malloc(env_variable_manager->variables.size + 1);
	if (!env)
		return (NULL);
	env[env_variable_manager->variables.size] = NULL;
	ft_memcpy(env, env_variable_manager->variables.data,
		env_variable_manager->variables.size);
	return (env);
}

char	*env_variable_manager_get_single(t_env_variables_manager *env_variable_manager,
		char *key)
{
	unsigned int	index;
	char			**element;

	index = 0;
	while (index < env_variable_manager->variables.size)
	{
		element = vec_get(&env_variable_manager->variables, index);
		if (ft_strcmp(key, *element) && (*element)[ft_strlen(key)] == '=')
			return (*element + ft_strlen(key) + 1);
	}
    return (NULL);
}

void	env_variables_manager_free(t_env_variables_manager *env_variable_manager)
{
	vec_free(&env_variable_manager->variables);
}
