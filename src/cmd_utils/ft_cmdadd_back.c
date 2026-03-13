/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:03:35 by lchamard          #+#    #+#             */
/*   Updated: 2026/02/17 08:58:38 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmdadd_back(t_cmd **cmd, t_cmd **new)
{
	t_cmd	*tmp;

	if (!(*cmd) && *new)
	{
		*cmd = *new;
		return ;
	}
	if (!(*cmd) || !(*new))
		return ;
	tmp = *cmd;
	tmp = ft_cmdlast(tmp);
	tmp->next = *new;
	(*new)->previous = tmp;
}
