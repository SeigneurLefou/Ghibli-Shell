/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/23 19:21:21 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_unset(int argc, char **argv, t_minishell *minishell)
{
	if (argc != 2)
	{
		write(2, "Unset needs one argument.\n", 27);
		return (1);
	}
	env_variable_manager_unset_key(&minishell->env_variables_manager, argv[1]);
	return (0);
}
