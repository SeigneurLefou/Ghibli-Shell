/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:11:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/20 17:46:26 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_export(int argc, char **argv, t_env_variables_manager *env_manager)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;

	if (argc > 2)
	{
		write(2, "Export needs no more than one argument <value>.\n", 49);
		return (1);
	}
	if (argc == 1)
	{
		it = iterator_new(&env_manager->variables, 0);
		index = 0;
		while (index < env_manager->variables.size)
		{
			element = iterator_next(&it);
			write(1, element, ft_strlen(element));
            write(1, "\n", 1);
			index++;
		}
		return (0);
	}
	if (!env_variables_manager_set_raw_line(env_manager, argv[1]))
		return (1);
	return (0);
}
