/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 09:38:42 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/16 17:01:55 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool is_command_built_in(char *name)
{
	const char *builtins[] = {"echo", "cd", "pwd", NULL};
	unsigned int index;
	
	index = 0;
	while (builtins[index])
	{
		if (!ft_strcmp(name, builtins[index]))
			return (true);
		index++;
	}
	return (false);
}

bool	exec_builtin(t_cmd *cmds)
{
	if (!ft_strcmp(cmds->name, "echo"))
		builtin_echo(cmds->argc, cmds->argv);
	if (!ft_strcmp(cmds->name, "cd"))
		builtin_cd(cmds->argc, cmds->argv);
	if (!ft_strcmp(cmds->name, "pwd"))
		builtin_pwd(cmds->argc, cmds->argv);
	return (false);
}
