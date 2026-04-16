/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_processus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:53:49 by lchamard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/15 19:05:21 by yben-dje         ###   ########.fr       */
=======
/*   Updated: 2026/04/16 13:44:39 by lchamard         ###   ########.fr       */
>>>>>>> b5af3f8 ([pipeline] fix the pipeline command but not the waitpid)
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

int	wait_all_pid(t_vec *pids)
{
	size_t	i;
	int		werror;

	werror = 0;
	i = 0;
	while (i < pids->size)
	{
		waitpid(*(int *)vec_get(pids, i), &werror, 0);
		i++;
	}
	vec_free(pids);
	return (werror);
}
