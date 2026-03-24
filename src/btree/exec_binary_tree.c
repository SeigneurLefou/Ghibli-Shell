/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:46:18 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/24 17:56:54 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_pipex	cmd_to_pipex(t_cmd *cmd, char **env)
{
	t_pipex	pipex_var;

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

int	exec_cmd(t_btree_node *tree, t_vec *expr, t_file files, char **env)
{
	t_pipex	pipex_var;

	vec_to_cmd(tree, expr, files, env)
	pipex_var = cmd_to_pipex(tree->cmds, env);
	execution_loop(&pipex_var);
	close(pipex_var.fds[0]);
	return (exit_code);
}

int	exec_binary_tree(t_btree_node *tree, t_vec *expr, int files[2], char **env)
{
	
	if (!tree->left && !tree->right)
		tree->wstatus = exec_cmd(tree, expr, files, env);
	if (tree->left)
		tree->wstatus = exec_binary_tree(tree->left, expr, files, env);
	files[0] = fake_fdin();
	if (!tree->left->wstatus && tree->operator == operator_and && tree->right)
	{
		wstatus_right = exec_binary_tree(tree->right, expr, files, env);
		tree->wstatus = tree->right->wstatus & tree->wstatus; 
	}
	else if (tree->left->wstatus && tree->operator == operator_or && tree->right)
	{
		wstatus_right = exec_binary_tree(tree->right, expr, files, env);
		tree->wstatus = tree->right->wstatus | tree->wstatus; 
	}
	else if (tree->operator == operator_semicolon && tree->right)
	{
		wstatus_right = exec_binary_tree(tree->right, expr, files, env);
		tree->wstatus = tree->right->wstatus;
	}
	else
		exec_pipeline(tree, env)
	return (tree->wstatus);
}
