/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:46:18 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/15 19:16:30 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	exec_cmd(t_btree *tree, int files[2], t_vec	*pid_list)
{
	t_pipex	pipex_var;

	vec_to_cmd(tree);
	pipex_var.pid = 0;
	tree->node->wstatus = 0;
	pipex_var.env = tree->env;
	pipex_var.cmd = tree->node->cmds;
	pipex_var.fds[0] = files[0];
	pipex_var.fds[1] = files[1];
	if (is_command_built_in(pipex_var.cmd->name))
		tree->node->wstatus = exec_builtin(pipex_var.cmd);
	else
		fork_pid(&pipex_var);

	vec_append(pid_list, &pipex_var.pid);

	if (pipex_var.fds[0] > 2)
		close(pipex_var.fds[0]);
	if (pipex_var.fds[1] > 2)
		close(pipex_var.fds[1]);
}

void	exec_right_pipeline(t_btree *tree, int files[2],
			t_vec *command_pid)
{
	t_btree	*tree_cpy;

	tree_cpy = malloc(sizeof(t_btree));
	cpy_btree(tree_cpy, tree);
	tree_cpy->node = tree_cpy->node->right;
	open_io_fds(tree_cpy, files);
	if (tree->node->operator != operator_pipe && !tree->node->wstatus
		&& tree->node->operator == operator_and )
		exec_pipeline(tree_cpy, files, command_pid);
	else if (tree->node->operator != operator_pipe && tree->node->wstatus
		&& tree->node->operator == operator_or )
		exec_pipeline(tree_cpy, files, command_pid);
	else if (tree->node->operator != operator_pipe
		&& tree->node->operator == operator_semicolon)
		exec_pipeline(tree_cpy, files, command_pid);
	else
		exec_pipeline(tree_cpy, files, command_pid);
}

void	exec_pipeline(t_btree *tree, int files[2], t_vec *pid_list)
{
	t_vec	command_pid;
	int		fd_out;
	int		pipe_fd[2];
	t_btree	*tree_cpy;
	
	tree_cpy = malloc(sizeof(t_btree));
	cpy_btree(tree_cpy, tree);
	vec_init(&command_pid, 1, 5);
	open_io_fds(tree_cpy, files);
	if (!tree->node->left && !tree->node->right)
	{

		exec_cmd(tree, files, &command_pid);

		vec_expand_and_free(pid_list, &command_pid);
		return ;
	}
	tree_cpy->node = tree_cpy->node->left;
	open_io_fds(tree_cpy, files);
	pipe(pipe_fd);
	fd_out = files[1];
	files[1] = pipe_fd[1];

	exec_pipeline(tree_cpy, files, &command_pid);
	if (command_pid.data)
		vec_expand_and_free(pid_list, &command_pid);
	files[0] = pipe_fd[0];
	files[1] = fd_out;
	exec_right_pipeline(tree, files, &command_pid);
	if (command_pid.data)
		vec_expand_and_free(pid_list, &command_pid);
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
}

int	exec_binary_tree(t_btree *tree, int files[2])
{
	t_vec	pid_list;
	t_btree	*tree_cpy;

	tree_cpy = malloc(sizeof(t_btree));
	cpy_btree(tree_cpy, tree);
	vec_init(&pid_list, sizeof(int), 5);
	open_io_fds(tree, files);
	if (!tree->node->left && !tree->node->right)
	{
		exec_cmd(tree, files, &pid_list);
		waitpid(*(int *)vec_get(&pid_list, 0), &tree->node->wstatus, 0);
		tree->node->wstatus = give_exit_code(tree->node->wstatus);
		return (tree->node->wstatus);
	}
	else if (tree->node->operator == operator_pipe)
	{
		exec_pipeline(tree, files, &pid_list);
		tree->node->wstatus = wait_all_pid(&pid_list);
		tree->node->wstatus = give_exit_code(tree->node->wstatus);
		return (tree->node->wstatus);
	}
	else if (tree->node->left)
	{
		tree_cpy->node = tree_cpy->node->left;
		exec_binary_tree(tree_cpy, files);
		tree->node->wstatus = tree_cpy->node->wstatus;
	}
	if (files[0])
		files[0] = fake_fdin();
	exec_right_tree(tree, files);
	return (tree->node->wstatus);
}
