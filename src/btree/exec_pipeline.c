/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:45:14 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/05 17:18:51 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

bool	exec_right_pipeline(t_btree *tree, int files[2], t_vec *command_pid)
{
	t_btree	*tree_cpy;
	int		new_files[2];

	new_files[0] = files[0];
	new_files[1] = files[1];
	tree_cpy = mem_alloc(sizeof(t_btree), default_error_exit, NULL, 0b1);
	cpy_btree(tree_cpy, tree);
	tree_cpy->node = tree_cpy->node->right;
	if (!open_io_fds(tree_cpy, new_files))
	{
		close_new_files(files, new_files);
		return (false);
	}
	if (tree->node->operator == operator_or && tree->node->wstatus)
		exec_pipeline(tree_cpy, new_files, command_pid);
	else if (tree->node->operator == operator_and && !tree->node->wstatus)
		exec_pipeline(tree_cpy, new_files, command_pid);
	else if (tree->node->operator == operator_pipe)
		exec_pipeline(tree_cpy, new_files, command_pid);
	mem_free(tree_cpy);
	close_new_files(files, new_files);
	return (true);
}

bool	exec_left_pipeline(t_btree *tree, int files[2], t_vec *command_pid)
{
	t_btree	*tree_cpy;
	int		new_files[2];

	new_files[0] = files[0];
	new_files[1] = files[1];
	tree_cpy = mem_alloc(sizeof(t_btree), default_error_exit, NULL, 0b1);
	cpy_btree(tree_cpy, tree);
	tree_cpy->node = tree_cpy->node->left;
	if (open_io_fds(tree_cpy, new_files))
		exec_pipeline(tree_cpy, new_files, command_pid);
	mem_free(tree_cpy);
	close_new_files(files, new_files);
	return (true);
}

bool	exec_left_right_pipeline(t_btree *tree, int files[2], t_vec *pid_list,
		t_vec *command_pid)
{
	int		pipe_fd[2];
	int		new_files[2];

	if (pipe(pipe_fd) < 0)
		return (false);
	new_files[0] = files[0];
	new_files[1] = pipe_fd[1];
	exec_left_pipeline(tree, new_files, command_pid);
	if (command_pid->data)
		vec_expand_and_free(pid_list, command_pid);
	vec_init(command_pid, sizeof(pid_t), 5);
	close_new_files(files, new_files);
	new_files[0] = pipe_fd[0];
	new_files[1] = files[1];
	if (!exec_right_pipeline(tree, new_files, command_pid))
		return (false);
	if (command_pid->data)
		vec_expand_and_free(pid_list, command_pid);
	close_new_files(files, new_files);
	return (true);
}

bool	exec_pipeline(t_btree *tree, int files[2], t_vec *pid_list)
{
	t_vec	command_pid;
	bool	return_value;

	vec_init(&command_pid, sizeof(pid_t), 5);
	if (!tree->node->left && !tree->node->right)
	{
		vec_to_cmd(tree);
		return_value = exec_cmd(tree, files, &command_pid);
		vec_expand_and_free(pid_list, &command_pid);
		return (return_value);
	}
	if (tree->node-> operator == operator_pipe)
		return_value = exec_left_right_pipeline(tree, files, pid_list,
				&command_pid);
	else
	{
		return_value = exec_binary_tree(tree, files);
		vec_append(&command_pid, &tree->node->wstatus);
		vec_free(&command_pid);
	}
	return (return_value);
}
