/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/24 12:39:39 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exit(int argc, t_minishell *minishell)
{
	if (argc != 1)
	{
		write(2, "Exit needs no argument.\n", 25);
		return (1);
	}
	minishell->request_exit = true;
	return (0);
}
