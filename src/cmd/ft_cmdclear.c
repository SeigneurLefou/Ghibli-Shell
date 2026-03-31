/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:03:31 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/27 10:46:09 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	ft_cmdclear(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp->argv[i])
	{
		free(tmp->argv[i]);
		i++;
	}
	free(tmp->argv);
	free(tmp->name);
	free(tmp->path);
	free(tmp);
	cmd = NULL;
}
