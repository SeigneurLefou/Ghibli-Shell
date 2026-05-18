/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:45:14 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/18 17:36:15 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	exec_right_pipeline(t_btree *tree, int files[2], t_vec *command_pid)
{
	t_btree	*tree_cpy;

	tree_cpy = malloc(sizeof(t_btree));
	cpy_btree(tree_cpy, tree);
	tree_cpy->node = tree_cpy->node->right;
	open_io_fds(tree_cpy, files);
	if (tree->node->operator != operator_pipe && !tree->node->wstatus
		&& tree->node->operator == operator_and)
		exec_pipeline(tree_cpy, files, command_pid);
	else if (tree->node->operator != operator_pipe && tree->node->wstatus
		&& tree->node->operator == operator_or)
		exec_pipeline(tree_cpy, files, command_pid);
	else if (tree->node->operator != operator_pipe
		&& tree->node->operator == operator_semicolon)
		exec_pipeline(tree_cpy, files, command_pid);
	else
		exec_pipeline(tree_cpy, files, command_pid);
	free(tree_cpy);
}

void	exec_left_right_pipeline(t_btree *tree, int files[2], t_vec *pid_list,
		t_vec *command_pid)
{
	t_btree	*tree_cpy;
	int		pipe_fd[2];
	int		fd_out;

	tree_cpy = malloc(sizeof(t_btree));
	cpy_btree(tree_cpy, tree);
	tree_cpy->node = tree_cpy->node->left;
	pipe(pipe_fd);
	fd_out = files[1];
	files[1] = pipe_fd[1];
	open_io_fds(tree_cpy, files);
	exec_pipeline(tree_cpy, files, command_pid);
	if ((*command_pid).data)
		vec_expand_and_free(pid_list, command_pid);
	free(tree_cpy);
	vec_init(command_pid, sizeof(pid_t), 5);
	files[0] = pipe_fd[0];
	files[1] = fd_out;
	open_io_fds(tree_cpy, files);
	exec_right_pipeline(tree, files, command_pid);
	if ((*command_pid).data)
		vec_expand_and_free(pid_list, command_pid);
}

void	exec_pipeline(t_btree *tree, int files[2], t_vec *pid_list)
{
	t_vec	command_pid;

	vec_init(&command_pid, sizeof(pid_t), 5);
	if (!tree->node->left && !tree->node->right)
	{
		vec_to_cmd(tree);
		exec_cmd(tree, files, &command_pid);
		printf("io fds after exec pipeline 0 : %d fd 1 : %d\n", files[0], files[1]);
		vec_expand_and_free(pid_list, &command_pid);
		return ;
	}
	exec_left_right_pipeline(tree, files, pid_list, &command_pid);
}
