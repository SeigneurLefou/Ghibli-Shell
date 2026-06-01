/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:03:31 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/01 15:02:16 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	ft_cmdclear(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp && tmp->argv && tmp->argv[i])
	{
		mem_free(tmp->argv[i]);
		i++;
	}
	if (tmp && tmp->argv)
		mem_free(tmp->argv);
	if (tmp && tmp->path)
		mem_free(tmp->path);
	if (tmp)
	{
		mem_free(tmp);
		cmd = NULL;
	}
}
