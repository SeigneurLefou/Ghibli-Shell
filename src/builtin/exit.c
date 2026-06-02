/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/02 14:44:59 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_numeric(char *num)
{
	unsigned int	index;

	index = 0;
	if (num[0] == '+' || num[0] == '-')
		index++;
	if (!num[index])
		return (false);
	while (num[index])
	{
		if (!ft_isdigit(num[index]))
			return (false);
		index++;
	}
	return (true);
}

int	builtin_exit(int argc, char **argv, t_minishell *minishell)
{
	bool	overflow;

	overflow = false;
	if (argc > 2)
	{
		write(2, "Exit needs at most one argument.\n", 34);
		return (1);
	}
	if (argc == 2)
		minishell->last_status = ft_atol_check_overflow(argv[1],
				&overflow) & 0xFF;
	minishell->request_exit = true;
	if (argc == 2 && !is_numeric(argv[1]))
	{
		write(2, "The argument is not a valid number. But bye!\n", 46);
		return (2);
	}
	if (argc == 2 && overflow)
	{
		write(2, "Exit code is larger than long max. But bye!\n", 45);
		return (2);
	}
	return (minishell->last_status);
}
