/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_processus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:53:49 by lchamard          #+#    #+#             */
/*   Updated: 2026/02/24 14:36:29 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	give_exit_code(int status)
{
	int	result;

	result = 0;
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		result = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		result = WSTOPSIG(status) + 128;
	return (result);
}

int	wait_all_pid(t_pipex *pipex_var)
{
	int	i;
	int	werror;

	werror = 0;
	i = 0;
	while (i < pipex_var->pid_i)
	{
		waitpid(pipex_var->pid[i], &werror, 0);
		i++;
	}
	free(pipex_var->pid);
	return (werror);
}
