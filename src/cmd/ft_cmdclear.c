/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:03:31 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 15:28:17 by lchamard         ###   ########.fr       */
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
		while (last->cmd_argv[i])
		{
			free(last->cmd_argv[i]);
			i++;
		}
		free(last->cmd_argv);
		free(last->cmd_path);
		free(last);
	}
	if (tmp)
		free(tmp);
	cmd = NULL;
}
