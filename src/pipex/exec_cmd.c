/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:46:01 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/12 17:44:45 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_fds(t_pipex *pipex_var)
{
	if (pipex_var->fds[0] > 2)
	{
		dup2(pipex_var->fds[0], 0);
		close(pipex_var->fds[0]);
	}
	if (pipex_var->fds[1] > 2)
	{
		dup2(pipex_var->fds[1], 1);
		close(pipex_var->fds[1]);
	}
	close_all_fds();
}

static void	exec_if_file_exists(t_pipex *pipex_var)
{
	char	**env;

	if (!access(pipex_var->cmd->path, F_OK))
	{
		if (!access(pipex_var->cmd->path, X_OK | F_OK))
		{
			env = env_variables_get_env(
					&pipex_var->minishell->env_variables_manager);
			execve(pipex_var->cmd->path, pipex_var->cmd->argv, env);
		}
		else
		{
			perror(pipex_var->cmd->name);
			ft_cmdclear(pipex_var->cmd);
			clear_garbage_collector();
			exit(126);
		}
	}
}

static void	command_not_found_error(t_pipex *pipex_var)
{
	write(2, pipex_var->cmd->name, ft_strlen(pipex_var->cmd->name));
	write(2, ": Command not found.\n", 22);
	ft_cmdclear(pipex_var->cmd);
	clear_garbage_collector();
	exit(127);
}

void	take_child(t_pipex *pipex_var)
{
	close_fds(pipex_var);
	if (is_command_built_in(pipex_var->cmd->name))
	{
		pipex_var->fds[0] = 0;
		pipex_var->fds[1] = 1;
		pipex_var->wstatus = exec_builtin(pipex_var->cmd, pipex_var->minishell,
				pipex_var->fds);
		ft_cmdclear(pipex_var->cmd);
		clear_garbage_collector();
		exit(pipex_var->wstatus);
	}
	else if (pipex_var->cmd->path && pipex_var->fds[0] != -1)
	{
		exec_if_file_exists(pipex_var);
		perror(pipex_var->cmd->name);
		if (!access(pipex_var->cmd->path, X_OK))
		{
			clear_garbage_collector();
			exit(126);
		}
		clear_garbage_collector();
		exit(127);
	}
	command_not_found_error(pipex_var);
}
