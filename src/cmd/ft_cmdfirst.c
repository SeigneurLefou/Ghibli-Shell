/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdfirst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 08:55:47 by lchamard          #+#    #+#             */
/*   Updated: 2026/02/17 11:20:13 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*ft_cmdfirst(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->previous)
	{
		tmp = tmp->previous;
	}
	return (tmp);
}
