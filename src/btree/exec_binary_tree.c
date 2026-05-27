/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:46:18 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/26 14:31:35 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

bool	exec_cmd(t_btree *tree, int files[2], t_vec *pid_list)
{
	t_pipex	pipex_var;

	pipex_var.pid = 0;
	tree->node->wstatus = 0;
	pipex_var.minishell = tree->minishell;
	pipex_var.cmd = tree->node->cmds;
	pipex_var.fds[0] = files[0];
	pipex_var.fds[1] = files[1];
	pipex_var.wstatus = 0;
	fork_pid(&pipex_var, tree->minishell->stdin_save);
	vec_append(pid_list, &pipex_var.pid);
	return (true);
}

bool	exec_right_tree(t_btree *tree, int files[2])
{
	t_btree	*tree_cpy;

	tree_cpy = mem_alloc(sizeof(t_btree), NULL, NULL, 0b1);
	cpy_btree(tree_cpy, tree);
	tree_cpy->node = tree_cpy->node->right;
	if (!tree->node->wstatus && tree->node->operator == operator_and)
	{
		exec_binary_tree(tree_cpy, files);
		tree->node->wstatus = tree_cpy->node->wstatus;
	}
	else if (tree->node->wstatus && tree->node->operator == operator_or)
	{
		exec_binary_tree(tree_cpy, files);
		tree->node->wstatus = tree_cpy->node->wstatus;
	}
	mem_free(tree_cpy);
	return (true);
}

bool	exec_left_tree(t_btree *tree, int files[2], t_vec *pid_list)
{
	t_btree	*tree_cpy;
	if (tree->node->operator== operator_pipe)
	{
		exec_pipeline(tree, files, pid_list);
		tree->node->wstatus = wait_all_pid(pid_list);
		tree->node->wstatus = give_exit_code(tree->node->wstatus);
		tree->minishell->last_status = tree->node->wstatus;
		return (false);
	}
	tree_cpy = mem_alloc(sizeof(t_btree), NULL, NULL, 0b1);
	cpy_btree(tree_cpy, tree);
	tree_cpy->node = tree_cpy->node->left;
	exec_binary_tree(tree_cpy, files);
	tree->node->wstatus = tree_cpy->node->wstatus;
	mem_free(tree_cpy);
	return (true);
}

bool	exec_leaf(t_btree *tree, int files[2], t_vec *pid_list)
{
	char	*status;

	vec_to_cmd(tree);
	if (is_command_built_in(tree->node->cmds->name))
	{
		setup_and_exec_builtin(tree, files);
		ft_cmdclear(tree->node->cmds);
	}
	else
	{
		exec_cmd(tree, files, pid_list);
		waitpid(*(pid_t *)vec_get(pid_list, 0), &tree->node->wstatus, 0);
		tree->node->wstatus = give_exit_code(tree->node->wstatus);
	}
	tree->minishell->last_status = tree->node->wstatus;
	status = ft_itoa(tree->node->wstatus);
	if (status)
		env_variables_set(&tree->minishell->env_variables_manager, "?",
			status);
	return (true);
}

bool	exec_binary_tree(t_btree *tree, int files[2])
{
	t_vec	pid_list;
	int		new_files[2];

	new_files[0] = files[0];
	new_files[1] = files[1];
	vec_init(&pid_list, sizeof(pid_t), 10);
	open_io_fds(tree, new_files, tree->minishell);
	if (!tree->node->left && !tree->node->right)
	{
		exec_leaf(tree, new_files, &pid_list);
		close_new_files(files, new_files, tree->minishell);
		return (true);
	}
	if (!exec_left_tree(tree, new_files, &pid_list))
		return (false);
	exec_right_tree(tree, new_files);
	tree->minishell->last_status = tree->node->wstatus;
	close_new_files(files, new_files, tree->minishell);
	return (true);
}
