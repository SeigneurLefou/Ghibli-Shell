/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:46:18 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/30 14:19:55 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_pipex	cmd_to_pipex(t_cmd *cmd, char **env)
{
	t_pipex	pipex_var;

	pipex_var.pid = ft_calloc(ft_cmdsize(&cmd), sizeof(int));
	pipex_var.pid_i = 0;
	pipex_var.env = env;
	pipex_var.cmd = cmd;
	return (pipex_var);
}

int	exec_pipe(t_tree *tree, char **env)
{
	int		werror;
	int		exit_code;
	t_pipex	pipex_var;
	t_cmd	*cmd_save;

	pipex_var = cmd_to_pipex(tree->cmds, env);
	execution_loop(&pipex_var);
	close(pipex_var.fds[0]);
	werror = wait_all_pid(&pipex_var);
	exit_code = give_exit_code(werror);
	return (exit_code);
}

int	exec_binary_tree(t_btree_node *tree, char **env)
{
	if (!tree->left && !tree->right)
		exec_pipe(tree, env);
	if (tree->left)
	{
		exec_binary_tree(tree->left, env);
		tree->wstatus = tree->left->wstatus; 
	}
	if (!tree->left->wstatus && tree->operator == operator_and && tree->right)
	{
		wstatus_right = exec_binary_tree(tree->right, env);
		tree->wstatus = tree->right->wstatus & tree->wstatus; 
	}
	else if (tree->left->wstatus && tree->operator == operator_or && tree->right)
	{
		wstatus_right = exec_binary_tree(tree->right, env);
		tree->wstatus = tree->right->wstatus | tree->wstatus; 
	}
	else if (tree->operator == operator_semicolon && tree->right)
	{
		wstatus_right = exec_binary_tree(tree->right, env);
		tree->wstatus = tree->right->wstatus;
	}
	return (tree->wstatus);
}
