/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:06:07 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/16 15:21:45 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*ft_cmdnew(char **cmd_line, int index)
{
	t_cmd	*new_cmd;
	char	**cmd_argv;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_argv = cmd_line;
	new_cmd->cmd_path g ft_ft_strcpy(cmd_argv[0]);
	new_cmd->next = NULL;
	new_cmd-iofile = ft_calloc(3, sizeof(char *))
	return (new_cmd);
}
