/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdshow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:04:02 by lchamard          #+#    #+#             */
/*   Updated: 2026/02/17 17:01:11 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmdshow(t_cmd *cmd)
{
	int		i;

	i = 0;
	ft_printf("previous [%p], cmd_name [%s], actual [%p], next [%p]\n",
		*cmd->previous, cmd->cmd_name, cmd, cmd->next);
	while (cmd->cmd_argv[i])
	{
		ft_printf("argv[%d] : [%s]\n", i, cmd->cmd_argv[i]);
		i++;
	}
}

void	ft_showallcmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	ft_putendl_fd("=== === === === ===", 1);
	while (tmp)
	{
		ft_cmdshow(tmp);
		tmp = tmp->next;
	}
	ft_putendl_fd("=== === === === ===", 1);
}
