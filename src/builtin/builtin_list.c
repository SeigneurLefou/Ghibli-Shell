/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 09:38:42 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/20 20:01:45 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool is_command_built_in(char *name)
{
	const char *builtins[] = {"echo", "cd", "pwd", "export", "source", NULL};
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

bool	exec_builtin(t_cmd *cmds, t_minishell *minishell)
{
	if (!ft_strcmp(cmds->name, "echo"))
		builtin_echo(cmds->argc, cmds->argv);
	if (!ft_strcmp(cmds->name, "cd"))
		builtin_cd(cmds->argc, cmds->argv, minishell);
	if (!ft_strcmp(cmds->name, "pwd"))
		builtin_pwd(cmds->argc);
	if (!ft_strcmp(cmds->name, "export"))
		builtin_export(cmds->argc, cmds->argv, minishell);
	if (!ft_strcmp(cmds->name, "source"))
		builtin_source(cmds->argc, cmds->argv, minishell);
	return (false);
}
