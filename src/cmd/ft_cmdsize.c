/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:06:18 by lchamard          #+#    #+#             */
/*   Updated: 2026/01/13 15:06:19 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cmdsize(t_cmd **cmd)
{
	size_t	len;
	t_cmd	*tmp;

	len = 1;
	if (!cmd)
		return (0);
	tmp = *cmd;
	if (!tmp)
		return (0);
	while (tmp->next)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
