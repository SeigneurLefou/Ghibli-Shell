/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:03:31 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/19 10:24:07 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	ft_cmdclear(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*last;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		last = tmp;
		tmp = tmp->next;
		i = 0;
		while (last->argv[i])
		{
			free(last->argv[i]);
			i++;
		}
		free(last->argv);
		free(last->path);
		free(last);
	}
	if (tmp)
		free(tmp);
	cmd = NULL;
}
