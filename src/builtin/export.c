/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:11:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/21 18:57:11 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_valid_key(char *line) {
  unsigned int i;

  if (!ft_isalpha(line[0]) && line[0] != '_')
    return (false);
  i = 0;
  while (line[i] &&
         !(line[i] == '=' || (line[i] == '+' && line[i + 1] == '='))) {
    if (!ft_isalnum(line[i]) && line[i] != '_')
      return (false);
    i++;
  }
  return (true);
}

static void	display_env_variables(t_minishell *minishell, int fds[2])
{
	unsigned int	index;
	char			*element;
	t_iterator		it;

	index = 0;
	it = iterator_new(&minishell->env_variables_manager.variables, 0);
	index = 0;
	while (index < minishell->env_variables_manager.variables.size)
	{
		element = iterator_next(&it);
		write(fds[1], element, ft_strlen(element));
		write(fds[1], "\n", 1);
		index++;
	}
}

static bool	handle_append(char *value, t_minishell *minishell, char *sep) {
  char *key;
  char *var_value;

  key = ft_substr(value, 0, sep - value - 1);
  if (!key)
    return (false);
  var_value = env_variables_get_raw(&minishell->env_variables_manager, key);
  if (!var_value || !ft_strchr(var_value, '=')) {
    if (!env_variables_set(&minishell->env_variables_manager, key, sep + 1))
      return (false);
    return (true);
  }
  mem_free(key);
  if (!var_value)
    return (true);
  var_value = ft_strjoin(var_value, sep + 1);
  if (!var_value)
    return (false);
  if (!env_variables_set_raw(&minishell->env_variables_manager, var_value)) {
    mem_free(var_value);
    return (false);
  }
  mem_free(var_value);
  return (true);
}

static bool	handle_setter(char *value, t_minishell *minishell) {
  char *sep;

  sep = ft_strchr(value, '=');
  if (sep && value != sep && *(sep - 1) == '+') {
    if (!handle_append(value, minishell, sep))
      return (false);
  } else if (!env_variables_set_raw(&minishell->env_variables_manager, value))
    return (false);
  return (true);
}

int	builtin_export(int argc, char **argv, t_minishell *minishell, int fds[2])
{
	if (argc > 2)
	{
		write(2, "Export needs no more than one argument <value>.\n", 49);
		return (1);
	}
	if (argc == 1)
	{
		display_env_variables(minishell, fds);
		return (0);
	}
	if (!is_valid_key(argv[1]))
	{
		write(2, "Export: not a valid identifier\n", 32);
		return (1);
	}
	if (!handle_setter(argv[1], minishell))
		return (1);
	return (0);
}
