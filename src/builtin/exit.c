/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/01 18:38:01 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(int argc, char **argv, t_minishell *minishell)
{
	bool overflow;

	overflow = false;
	if (argc > 2)
	{
		write(2, "Exit needs at most one argument.\n", 34);
		return (1);
	}
	if (argc == 2)
		minishell->last_status = ft_atol_check_overflow(argv[1], &overflow) & 0xFF;
	minishell->request_exit = true;
	if (overflow)
	{
		write(2, "Exit code is larger than long max. But bye!\n", 45);
		return (2);
	}
	return (minishell->last_status);
}
