/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/01 14:15:11 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(int argc, char **argv, t_minishell *minishell)
{
	int	index;

	index = 1;
	if (argc < 2)
	{
		write(2, "Unset needs at least one argument.\n", 36);
		return (1);
	}
	while (index < argc)
		env_variables_unset_key(&minishell->env_variables_manager,
			argv[index++]);
	return (0);
}
