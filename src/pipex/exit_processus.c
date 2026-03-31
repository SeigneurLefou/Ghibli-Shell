/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_processus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:53:49 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/27 11:28:19 by lchamard         ###   ########.fr       */
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

int	wait_all_pid(t_pid_list *pids)
{
	size_t	i;
	int		werror;

	werror = 0;
	i = 0;
	while (i < pids->len)
	{
		waitpid(pids->pids[i], &werror, 0);
		i++;
	}
	free(pids->pids);
	return (werror);
}
