/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 09:38:42 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/01 14:11:26 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	is_command_built_in(char *name)
{
	const char		*builtins[] = {"echo", "cd", "pwd", "export",
		"source", "unset", "exit", "env", NULL};
	unsigned int	index;

	index = 0;
	if (!name)
		return (false);
	while (builtins[index])
	{
		if (!ft_strcmp(name, builtins[index]))
			return (true);
		index++;
	}
	return (false);
}

int	exec_builtin(t_cmd *cmds, t_minishell *minishell, int fds[2])
{
	int	result;

	result = -1;
	if (!ft_strcmp(cmds->name, "echo"))
		result = builtin_echo(cmds->argc, cmds->argv, fds);
	if (!ft_strcmp(cmds->name, "cd"))
		result = builtin_cd(cmds->argc, cmds->argv, minishell);
	if (!ft_strcmp(cmds->name, "pwd"))
		result = builtin_pwd(cmds->argc, fds);
	if (!ft_strcmp(cmds->name, "export"))
		result = builtin_export(cmds->argc, cmds->argv, minishell, fds);
	if (!ft_strcmp(cmds->name, "source"))
		result = builtin_source(cmds->argc, cmds->argv, minishell);
	if (!ft_strcmp(cmds->name, "unset"))
		result = builtin_unset(cmds->argc, cmds->argv, minishell);
	if (!ft_strcmp(cmds->name, "exit"))
		result = builtin_exit(cmds->argc, cmds->argv, minishell);
	if (!ft_strcmp(cmds->name, "env"))
		result = builtin_env(cmds->argc, minishell, fds);
	return (result);
}

bool	setup_and_exec_builtin(t_btree *tree, int files[2])
{
	t_pipex	pipex_var;

	pipex_var.pid = 0;
	tree->node->wstatus = -1;
	pipex_var.minishell = tree->minishell;
	pipex_var.cmd = tree->node->cmds;
	pipex_var.fds[0] = files[0];
	pipex_var.fds[1] = files[1];
	tree->node->wstatus = exec_builtin(pipex_var.cmd, tree->minishell,
			pipex_var.fds);
	return (false);
}
