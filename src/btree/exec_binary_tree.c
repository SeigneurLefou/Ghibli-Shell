/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:46:18 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/05 11:29:14 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	exec_cmd(t_btree *tree, int files[2], t_vec	*pid_list)
{
	t_pipex	pipex_var;

	pipex_var.pid = 0;
	tree->node->wstatus = 0;
	pipex_var.minishell = tree->minishell;
	pipex_var.cmd = tree->node->cmds;
	pipex_var.fds[0] = files[0];
	pipex_var.fds[1] = files[1];
	fork_pid(&pipex_var);
	vec_append(pid_list, &pipex_var.pid);
	if (pipex_var.fds[0] > 2)
		close(pipex_var.fds[0]);
	if (pipex_var.fds[1] > 2)
		close(pipex_var.fds[1]);
	ft_cmdclear(tree->node->cmds);
}

void	exec_right_tree(t_btree *tree, int files[2])
{
	t_btree	*tree_cpy;

	tree_cpy = malloc(sizeof(t_btree));
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
	free(tree_cpy);
}

bool	exec_left_tree(t_btree *tree, int files[2], t_vec *pid_list)
{
	t_btree	*tree_cpy;

	if (tree->node->operator == operator_pipe)
	{
		exec_pipeline(tree, files, pid_list);
		tree->node->wstatus = wait_all_pid(pid_list);
		tree->node->wstatus = give_exit_code(tree->node->wstatus);
		// env_variable_manager_set(&tree->minishell->env_variables_manager, "?",
				// ft_itoa(tree->node->wstatus));
		return (true);
	}
	tree_cpy = malloc(sizeof(t_btree));
	cpy_btree(tree_cpy, tree);
	tree_cpy->node = tree_cpy->node->left;
	exec_binary_tree(tree_cpy, files);
	tree->node->wstatus = tree_cpy->node->wstatus;
	free(tree_cpy);
	return (false);
}

bool	exec_leaf(t_btree *tree, int files[2], t_vec *pid_list)
{
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
	// env_variable_manager_set(&tree->minishell->env_variables_manager, "?",
			// ft_itoa(tree->node->wstatus));
	return (tree->node->wstatus);
}

int	exec_binary_tree(t_btree *tree, int files[2])
{
	t_vec	pid_list;
	int		wstatus;

	vec_init(&pid_list, sizeof(pid_t), 10);
	open_io_fds(tree, files);
	if (!tree->node->left && !tree->node->right)
		return (exec_leaf(tree, files, &pid_list));
	if (exec_left_tree(tree, files, &pid_list))
		return (tree->node->wstatus);
	if (files[0])
		files[0] = fake_fdin();
	exec_right_tree(tree, files);
	wstatus = tree->node->wstatus;
	// env_variable_manager_set(&tree->minishell->env_variables_manager, "?",
			// ft_itoa(tree->node->wstatus));
	return (wstatus);
}
