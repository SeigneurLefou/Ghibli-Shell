/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:34:44 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/29 18:19:41 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_env_variables_manager	env_variables_new(void) {
  t_env_variables_manager env_variable_manager;

  env_variable_manager.variables = list_new();
  return (env_variable_manager);
}

bool	env_variables_set_raw(t_env_variables_manager *env_variable_manager,
		char *line)
{
	char	*new;
	char	*key;
	char	*sep;
	bool	exists;
	
	sep = ft_strchr(line, '=');
	if (!sep)
		key = ft_strdup(line);
	else
		key = ft_substr(line, 0, sep - line);
	new = ft_strdup(line);
	if (!new || !key)
		return (false);
	exists = env_variables_exists(env_variable_manager, key);
	if (exists && sep)
		env_variables_unset_key(env_variable_manager, key);
	mem_free(key);
	if (!(exists && !sep) && !list_push_back(&env_variable_manager->variables,
			new))
		return (false);
	return (true);
}

char	*env_variables_get_raw(t_env_variables_manager *env_variable_manager,
                            char *key) {
  unsigned int index;
  char *element;
  t_iterator it;
  int key_len;

  key_len = ft_strlen(key);
  it = iterator_new(&env_variable_manager->variables, 0);
  index = 0;
  while (index < env_variable_manager->variables.size) {
    element = iterator_next(&it);
    if ((int)ft_strlen(element) >= key_len &&
        !ft_strncmp(key, element, key_len) &&
        (!element[key_len] || element[key_len] == '='))
      return (element);
    index++;
  }
  return (NULL);
}

static char	*env_variables_manager_create_line(char *key, char *value) {
  char *line;
  unsigned int key_size;
  unsigned int value_size;

  key_size = ft_strlen(key);
  value_size = ft_strlen(value);
  line = mem_alloc(key_size + value_size + 2, default_error_exit, NULL, 0b1);
  if (!line)
    return (NULL);
  ft_memcpy(line, key, key_size);
  ft_memcpy(line + key_size + 1, value, value_size);
  line[key_size] = '=';
  line[key_size + value_size + 1] = 0;
  return (line);
}

bool	env_variables_add(t_env_variables_manager *env_variable_manager,
		char *key,
                       char *value) {
  char *line;

  line = env_variables_manager_create_line(key, value);
  list_push_back(&env_variable_manager->variables, line);
  return (true);
}

char	**env_variables_get_env(t_env_variables_manager *env_variable_manager) {
  char **env;
  t_iterator it;
  unsigned int index;

  env = mem_alloc(sizeof(char *) * (env_variable_manager->variables.size + 1),
                  default_error_exit, NULL, 0b1);
  if (!env)
    return (NULL);
  env[env_variable_manager->variables.size] = NULL;
  it = iterator_new(&env_variable_manager->variables, 0);
  index = 0;
  while (index < env_variable_manager->variables.size) {
    env[index] = iterator_next(&it);
    index++;
  }
  return (env);
}

char	*env_variables_get(t_env_variables_manager *env_variable_manager,
                        char *key) {
  unsigned int index;
  char *element;
  t_iterator it;
  int key_len;

  key_len = ft_strlen(key);
  it = iterator_new(&env_variable_manager->variables, 0);
  index = 0;
  while (index < env_variable_manager->variables.size) {
    element = iterator_next(&it);
    if ((int)ft_strlen(element) >= key_len &&
        !ft_strncmp(key, element, key_len) &&
        (!element[key_len] || element[key_len] == '='))
      return (element + key_len + (element[key_len] == '='));
    index++;
  }
  return (NULL);
}

bool	env_variables_exists(t_env_variables_manager *env_variable_manager,
                          char *key) {
  unsigned int index;
  char *element;
  t_iterator it;
  int key_len;

  key_len = ft_strlen(key);
  it = iterator_new(&env_variable_manager->variables, 0);
  index = 0;
  while (index < env_variable_manager->variables.size) {
    element = iterator_next(&it);
    if (!ft_strncmp(key, element, key_len) &&
        (!element[key_len] || element[key_len] == '='))
      return (true);
    index++;
  }
  return (false);
}

bool	env_variables_set(t_env_variables_manager *env_variable_manager,
		char *key,
                       char *value) {
  unsigned int index;
  char *element;
  t_iterator it;
  t_list_cell *cell;
  int key_len;

  key_len = ft_strlen(key);
  it = iterator_new(&env_variable_manager->variables, 0);
  index = 0;
  while (index < env_variable_manager->variables.size) {
    element = iterator_next(&it);
    if (!ft_strncmp(key, element, key_len) &&
        (!element[key_len] || element[key_len] == '=')) {
      cell = list_get_cell_at_index(&env_variable_manager->variables, index);
      mem_free(cell->value);
      cell->value = env_variables_manager_create_line(key, value);
      return (cell->value != 0);
    }
    index++;
  }
  if (!env_variables_add(env_variable_manager, key, value))
    return (false);
  return (true);
}

bool	env_variables_unset_key(t_env_variables_manager *env_variable_manager,
                             char *key) {
  unsigned int index;
  char *element;
  t_iterator it;
  int key_len;

  key_len = ft_strlen(key);
  it = iterator_new(&env_variable_manager->variables, 0);
  index = 0;
  while (index < env_variable_manager->variables.size) {
    element = iterator_next(&it);
    if (!ft_strncmp(key, element, key_len) &&
        (!element[key_len] || element[key_len] == '=')) {
      list_pop_at_free(&env_variable_manager->variables, index, mem_free);
      return (true);
    }
    index++;
  }
  return (false);
}

void	env_variables_free(t_env_variables_manager *env_variable_manager) {
  list_clear(&env_variable_manager->variables, mem_free);
}

void	env_variables_add_from_env(t_env_variables_manager *env_variable_manager,
                                char **env) {
  unsigned int index;

  index = 0;
  while (env[index]) {
    if (!env_variables_set_raw(env_variable_manager, env[index])) {
      memory_allocation_failed_error_exit();
    }
    index++;
  }
}
