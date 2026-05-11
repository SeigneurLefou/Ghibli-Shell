/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:11:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/11 18:42:12 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_valid_key(char *line)
{
	unsigned int	i;

	if (!ft_isalpha(line[0]) && line[0] != '_')
		return (false);
	i = 0;
	while (line[i] && !(line[i] == '=' || (line[i] != '+' && line[i + 1] != '=')))
	{
		if (!ft_isalnum(line[i]) && line[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	display_env_variables(t_minishell *minishell)
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
		write(1, element, ft_strlen(element));
		write(1, "\n", 1);
		index++;
	}
}

int	builtin_export(int argc, char **argv, t_minishell *minishell)
{
	if (argc > 2)
	{
		write(2, "Export needs no more than one argument <value>.\n", 49);
		return (1);
	}
	if (argc == 1)
	{
		display_env_variables(minishell);
		return (0);
	}
	if (!is_valid_key(argv[1]))
	{
		write(2, "Export: not a valid identifier\n", 32);
		return (1);
	}
	// TODO: Handle += 
	if (!env_variables_manager_set_raw_line(&minishell->env_variables_manager,
			argv[1]))
		return (1);
	return (0);
}
