/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:57:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/26 17:37:10 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_pid(t_pipex *pipex_var)
{
	pipex_var->pid = fork();
	if (pipex_var->pid == -1)
		return (1);
	else if (pipex_var->pid == 0)
		take_child(pipex_var);
	return (0);
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
