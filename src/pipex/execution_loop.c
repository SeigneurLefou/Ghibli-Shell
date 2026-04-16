/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:57:48 by lchamard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/15 17:08:14 by yben-dje         ###   ########.fr       */
=======
/*   Updated: 2026/04/16 11:38:43 by lchamard         ###   ########.fr       */
>>>>>>> b5af3f8 ([pipeline] fix the pipeline command but not the waitpid)
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
