/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:57:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/05 17:23:55 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_pid(t_pipex	*pipex_var, char *cmd_path)
{
	pipex_var->pid[pipex_var->pid_i] = fork();
	pipex_var->pid_i++;
	if (pipex_var->pid[pipex_var->pid_i - 1] == -1)
		return (-1);
	else if (pipex_var->pid[pipex_var->pid_i - 1] == 0)
		take_child(pipex_var, cmd_path);
	close(pipex_var->fd[0]);
	close(pipex_var->fd[2]);
	return (pipex_var->fd[1]);
}

int	child_gestion(t_pipex *pipex_var)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(pipex_var);
	if (!cmd_path)
	{
		if (errno)
			perror(pipex_var->cmd->cmd_name);
		close(pipex_var->fd[0]);
		close(pipex_var->fd[1]);
		close(pipex_var->fd[2]);
		pipex_var->fd[0] = fake_fdin();
		return (1);
	}
	pipex_var->fd[0] = fork_pid(pipex_var, cmd_path);
	if (cmd_path)
		free(cmd_path);
	if (pipex_var->fd[0] == -1)
		return (1);
	if (!pipex_var->cmd->next)
		return (1);
	return (0);
}

int	pipe_gestion(t_pipex *pipex_var, int open_flag)
{
	int		pipe_error;

	pipe_error = pipe(&pipex_var->fd[1]);
	if (pipe_error || !(pipex_var->cmd->next))
	{
		close(pipex_var->fd[2]);
		close(pipex_var->fd[1]);
		if (!pipe_error)
			pipex_var->fd[2] = open(pipex_var->outfile,
					O_CREAT | O_WRONLY | open_flag, 0644);
		if (pipex_var->fd[2] == -1 || pipe_error)
			return (1);
	}
	return (0);
}

int	execution_loop(t_pipex *pipex_var)
{
	while (pipex_var->cmd)
	{
		if (!(pipex_var->cmd->next) && !access(pipex_var->outfile, F_OK)
			&& access(pipex_var->outfile, W_OK))
		{
			if (errno)
				perror(pipex_var->cmd->cmd_name);
			return (1);
		}
		if (pipe_gestion(pipex_var, O_TRUNC))
			return (1);
		child_gestion(pipex_var);
		pipex_var->cmd = pipex_var->cmd->next;
	}
	return (0);
}

int	execution_loop_here_doc(t_pipex *pipex_var)
{
	while (pipex_var->cmd)
	{
		if (!(pipex_var->cmd->next) && !access(pipex_var->outfile, F_OK)
			&& access(pipex_var->outfile, W_OK))
		{
			if (errno)
				perror(pipex_var->cmd->cmd_name);
			return (1);
		}
		if (pipe_gestion(pipex_var, O_APPEND))
			return (1);
		child_gestion(pipex_var);
		pipex_var->cmd = pipex_var->cmd->next;
	}
	return (0);
}
