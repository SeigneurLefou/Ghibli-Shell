/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:03:41 by lchamard          #+#    #+#             */
/*   Updated: 2026/01/13 15:03:42 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmdadd_front(t_cmd **cmd, t_cmd **new)
{
	if (!(*cmd) || !(*new))
	{
		*cmd = *new;
		return ;
	}
	(*cmd)->previous = *new;
	(*new)->next = *cmd;
	*cmd = *new;
}
