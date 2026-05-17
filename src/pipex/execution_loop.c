/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:57:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/17 19:06:43 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_pid(t_pipex *pipex_var, int stdin_pid_copy)
{
	pipex_var->pid = fork();
	if (pipex_var->pid == -1)
		return (1);
	else if (pipex_var->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		close(stdin_pid_copy);
		take_child(pipex_var);
	}
	return (0);
}
