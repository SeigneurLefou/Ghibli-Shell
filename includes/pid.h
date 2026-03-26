/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:21:34 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/26 09:21:35 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PID_H
# define PID_H

# include "stdlib.h"

typedef struct s_pid_list
{
	int		*pids;
	size_t	len;
}				t_pid_list;

void	pid_append(t_pid_list *pid_list);

#endif
