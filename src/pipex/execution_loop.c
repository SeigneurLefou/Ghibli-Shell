/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:57:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/26 08:07:24 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_pid(t_pipex *pipex_var)
{
	pipex_var->pid = fork();
	if (pipex_var->pid[pipex_var->pid_i - 1] == -1)
		return ;
	else if (pipex_var->pid[pipex_var->pid_i - 1] == 0)
		take_child(pipex_var);
}

int	child_gestion(t_pipex *pipex_var)
{
	fork_pid(pipex_var);
	return (0);
}

int	execution_loop(t_pipex *pipex_var)
{
	child_gestion(pipex_var);
	return (0);
}
