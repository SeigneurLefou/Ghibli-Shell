/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:51:23 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/25 13:41:36 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pid.h"

void	pid_append(t_pid_list *pid_list, int nb)
{
	int		*new_pid_list;
	size_t	i;

	i = 0;
	if (!pid_list)
		pid_list->len = 1;
	else
		pid_list->len++;
	new_pid_list = malloc(sizeof(int) * pid_list->len);
	while(i < pid_list->len)
	{
		new_pid_list[i] = pid_list->pids[i];
		i++;
	}
	new_pid_list[i] = nb;
	pid_list->pids = new_pid_list;
}

void	pid_expend(t_pid_list *pid_list, t_pid_list *pid_list_to_extend)
{
	int		*new_pid_list;
	size_t	i;

	i = 0;
	if (!pid_list)
		pid_list->len = pid_list_to_extend->len;
	else
		pid_list->len += pid_list_to_extend->len;
	new_pid_list = malloc(sizeof(int) * pid_list->len);
	while(i < pid_list->len)
	{
		new_pid_list[i] = pid_list->pids[i];
		i++;
	}
	i = 0;
	while(i < pid_list_to_extend->len)
	{
		new_pid_list[i] = pid_list_to_extend->pids[i];
		i++;
	}
	pid_list->pids = new_pid_list;
}
