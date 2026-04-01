/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:21:34 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/31 17:14:47 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PID_H
# define PID_H

# include "stdlib.h"
# include <stdio.h>

typedef struct s_pid_list
{
	int		*pids;
	size_t	len;
}				t_pid_list;

void	pid_append(t_pid_list *pid_list, int nb);
void	pid_extend(t_pid_list *pid_list, t_pid_list *pid_list_to_extend);

#endif
