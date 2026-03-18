/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:46:18 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/18 10:00:15 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_pipex	cmd_to_pipex(t_cmd *cmd, char **env)
{
	t_pipex	pipex_var;

	pipex_var.pid = ft_calloc(ft_cmdsize(cmd), sizeof(int));
	pipex_var.pid_i = 0;
	pipex_var.env = env;
	pipex_var.cmd = cmd;
}

int	exec_pipe(t_cmd cmds, char **env)
{
	int		werror;
	int		exit_code;
	t_pipex	pipex_var;
	t_cmd	*cmd_save;

	if (!cmds)
	{
		ft_printf(strerror(EINVAL));
		exit(1);
	}
	pipex_var = cmd_to_pipex(cmds);
	execution_loop(&pipex_var);
	close(pipex_var.fd[0]);
	werror = wait_all_pid(&pipex_var);
	exit_code = give_exit_code(werror);
	exit(exit_code);
}

int	exec_binary_tree(t_btree *tree, char **env)
{
	int	wstatus_left;
	int	wstatus_right;

	if (!tree->left && !tree->right)
		wstatus_left = exec_pipe(tree->node);
	if (tree->left)
		wstatus_left = exec_binary_tree(tree->left);
	if (!wstatus_left && tree->operator == operator_and && tree->right)
		wstatus_right = exec_binary_tree(tree->right);
	else if (wstatus_left && tree->operator == operator_or && tree->right)
		wstatus_right = exec_binary_tree(tree->right);
	else if (tree->operator == operator_semicolon && tree->right)
		wstatus_right = exec_binary_tree(tree->right);
	if (tree->operator == operator_and)
		return (wstatus_left & wstatus_right);
	else if (tree->operator == operator_or)
		return (wstatus_left | wstatus_right);
	else if (tree->operator == operator_semicolon)
		return (wstatus_right);
}
