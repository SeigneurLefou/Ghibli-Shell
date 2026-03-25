/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:46:18 by lchamard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/03/30 14:31:50 by lchamard         ###   ########.fr       */
=======
/*   Updated: 2026/03/25 13:46:01 by lchamard         ###   ########.fr       */
>>>>>>> 53d9926 ([give pid] : give pid list to the previous command for then the pipe on the tap wait all pid.)
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

int	exec_cmd(t_btree_node *tree, t_vec *expr, t_file files, char **env)
{
	t_pipex		pipex_var;
	t_pid_list	pid_list;
	int			pid;

	vec_to_cmd(tree, expr, files, env)
	pipex_var = cmd_to_pipex(tree->cmds, env);
	pid = execution_loop(&pipex_var);
	pid_append(pid_list, pid);
	close(pipex_var.fds[0]);
	return (exit_code);
}

int	exec_pipeline(t_tree *tree, t_vec *expr, int files[2], char **env)
{
	t_pid_list	pid;
	t_pid_list	command_pid;
	int	fd_out;
	int	pipe_fd[2]

	fd_out = files[1];
	files[1] = pipe_fd[1];
	if (!tree->left && !tree->right)
		command_pid = exec_cmd(tree, expr, files, env);
	else if (tree->operator == operator_pipe)
		command_pid = exec_pipeline(tree, expr, files, env);
	files[0] = pipe_fd[0];
	files[1] = fd_out;
	if (command_pid)
	{
		pid_extend(&pid, &command_pid);
		free(command_pid);
		command_pid = NULL;
	}
	if (tree->operator != operator_pipe && !tree->left->wstatus && tree->operator == operator_and && tree->right)
		command_pid = exec_pipeline(tree->right, expr, files, env);
	else if (tree->operator != operator_pipe && tree->left->wstatus && tree->operator == operator_or && tree->right)
		command_pid = exec_pipeline(tree->right, expr, files, env);
	else if (tree->operator != operator_pipe && tree->operator == operator_semicolon && tree->right)
		command_pid = exec_pipeline(tree->right, expr, files, env);
	else
		command_pid = exec_pipeline(tree->right, expr, files, env);
	if (command_pid)
	{
		pid_extend(&pid, &command_pid);
		free(command_pid);
	}
	return (pid);
}

int	exec_binary_tree(t_btree_node *tree, t_vec *expr, int files[2], char **env)
{
	t_pid	pid_list;
	
	if (!tree->left && !tree->right)
	{
		pid_list = exec_cmd(tree, expr, files, env);
		waitpid(pid_list->pids[0], &tree->wstatus, 1);
		tree->wstatus = give_exit_code(tree->wstatus);
	}
	if (tree->operator == operator_pipe)
	{
		pid_list = exec_pipeline(tree, expr, files, env);
		&tree->wstatus = wait_all_pid(pid_list); 
		tree->wstatus = give_exit_code(tree->wstatus);
	}
	if (tree->operator != operator_pipe && tree->left)
	{
		exec_binary_tree(tree->left, expr, files, env);
		tree->wstatus = tree->left->wstatus; 
	}
	files[0] = fake_fdin();
	if (tree->operator != operator_pipe && !tree->left->wstatus && tree->operator == operator_and && tree->right)
	{
		exec_binary_tree(tree->right, expr, files, env);
		tree->wstatus = tree->right->wstatus & tree->wstatus; 
	}
	else if (tree->operator != operator_pipe && tree->left->wstatus && tree->operator == operator_or && tree->right)
	{
		exec_binary_tree(tree->right, expr, files, env);
		tree->wstatus = tree->right->wstatus | tree->wstatus; 
	}
	else if (tree->operator != operator_pipe && tree->operator == operator_semicolon && tree->right)
	{
		exec_binary_tree(tree->right, expr, files, env);
		tree->wstatus = tree->right->wstatus;
	}
	return (tree->wstatus);
}
