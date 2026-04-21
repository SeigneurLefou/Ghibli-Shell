/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 09:38:42 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/21 09:55:48 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool is_command_built_in(char *name)
{
	const char *builtins[] = {"echo", "cd", "pwd", "export", NULL};
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

bool	exec_builtin(t_cmd *cmds, t_env_variables_manager *env_manager)
{
	if (!ft_strcmp(cmds->name, "echo"))
		builtin_echo(cmds->argc, cmds->argv);
	if (!ft_strcmp(cmds->name, "cd"))
		builtin_cd(cmds->argc, cmds->argv, env_manager);
	if (!ft_strcmp(cmds->name, "pwd"))
		builtin_pwd(cmds->argc, cmds->argv);
	if (!ft_strcmp(cmds->name, "export"))
		builtin_export(cmds->argc, cmds->argv, env_manager);
	return (false);
}

bool	pre_exec_builtin(t_btree *tree, int files[2])
{
	t_pipex	pipex_var;

	printf("OOOH\n");
	vec_to_cmd(tree);
	pipex_var.pid = 0;
	tree->node->wstatus = -1;
	pipex_var.minishell = tree->minishell;
	pipex_var.cmd = tree->node->cmds;
	pipex_var.fds[0] = files[0];
	pipex_var.fds[1] = files[1];
	exec_builtin(pipex_var.cmd, &tree->minishell->env_variables_manager);
	if (pipex_var.fds[0] > 2)
		close(pipex_var.fds[0]);
	if (pipex_var.fds[1] > 2)
		close(pipex_var.fds[1]);
	return (false);
}

