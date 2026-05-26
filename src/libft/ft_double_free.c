/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:32:40 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/18 19:15:24 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_double_mem_free(char **double_list)
{
	size_t	i;

	i = 0;
	while (double_list[i])
	{
		mem_free(double_list[i]);
		i++;
	}
	mem_free(double_list);
}

void	ft_double_free_start(char **double_list, int start)
{
	size_t	i;

	i = start;
	while (double_list[i])
	{
		mem_free(double_list[i]);
		i++;
	}
	mem_free(double_list);
}
