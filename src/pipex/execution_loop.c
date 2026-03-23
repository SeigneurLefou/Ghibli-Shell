/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:57:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/23 10:08:55 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_pid(t_pipex *pipex_var)
{
	pipex_var->pid[pipex_var->pid_i] = fork();
	pipex_var->pid_i++;
	if (pipex_var->pid[pipex_var->pid_i - 1] == -1)
		return (-1);
	else if (pipex_var->pid[pipex_var->pid_i - 1] == 0)
		take_child(pipex_var);
	close(pipex_var->fds[0]);
	close(pipex_var->fds[2]);
	return (pipex_var->fds[1]);
}

int	child_gestion(t_pipex *pipex_var)
{
	if (!pipex_var->cmd->path)
	{
		if (errno)
			perror(pipex_var->cmd->name);
		close(pipex_var->fds[0]);
		close(pipex_var->fds[1]);
		close(pipex_var->fds[2]);
		pipex_var->fds[0] = fake_fdin();
		return (1);
	}
	pipex_var->fds[0] = fork_pid(pipex_var);
	if (pipex_var->fds[0] == -1)
		return (1);
	if (!pipex_var->cmd->next)
		return (1);
	return (0);
}

int	pipe_gestion(t_pipex *pipex_var)
{
	int		pipe_error;

	if (pipex_var->cmd->output_file)
	{
		if (!access(pipex_var->cmd->output_file, F_OK)
			&& access(pipex_var->cmd->output_file, W_OK))
		{
			if (errno)
				perror(pipex_var->cmd->name);
			return (1);
		}
		pipex_var->fds[2] = open(pipex_var->cmd->output_file,
				O_CREAT | O_WRONLY | pipex_var->cmd->open_mode, 0644);
		if (pipex_var->fds[2] == -1)
			return (1);
	}
	else
	{
		pipe_error = pipe(&pipex_var->fds[1]);
		if (pipe_error)
			return (1);
	}
	return (0);
}

int	infile_gestion(t_pipex *pipex_var)
{
	if (pipex_var->cmd->input_file)
	{
		if (pipex_var->cmd->is_heredoc)
			pipex_var->fds[0] = here_doc_file(pipex_var->cmd->input_file);
		else if (pipex_var->cmd->input_file)
			pipex_var->fds[0] = open(pipex_var->cmd->input_file, O_RDONLY, 0644);
		if (errno)
			perror(pipex_var->cmd->input_file);
		if (pipex_var->fds[0] == -1)
			return (1);
	}
	return (0);
}

int	execution_loop(t_pipex *pipex_var)
{
	while (pipex_var->cmd)
	{
		if (infile_gestion(pipex_var))
			return (1);
		if (pipe_gestion(pipex_var))
			return (1);
		child_gestion(pipex_var);
		pipex_var->cmd = pipex_var->cmd->next;
	}
	return (0);
}
