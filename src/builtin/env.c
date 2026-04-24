/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:11:01 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/24 10:46:09 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(int argc, t_minishell *minishell)
{
	unsigned int	index;
	char			*element;
	t_iterator		it;

	if (argc > 1)
	{
		write(2, "Env does not support more than one argument.\n", 46);
		return (1);
	}
	it = iterator_new(&minishell->env_variables_manager.variables, 0);
	index = 0;
	while (index < minishell->env_variables_manager.variables.size)
	{
		element = iterator_next(&it);
		write(1, element, ft_strlen(element));
		write(1, "\n", 1);
		index++;
	}
	return (0);
}
