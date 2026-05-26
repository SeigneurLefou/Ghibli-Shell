/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/26 17:32:20 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(int argc, char **argv, t_minishell *minishell)
{
	if (argc > 2)
	{
		write(2, "Exit needs at most one argument.\n", 34);
		return (1);
	}
	if (argc == 2)
		minishell->last_status = ft_atol(argv[1]) % 255;
	minishell->request_exit = true;
	return (minishell->last_status);
}
