/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:32:40 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 09:41:52 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_double_free(char **double_list)
{
	size_t	i;

	i = 0;
	while (double_list[i])
	{
		free(double_list[i]);
		i++;
	}
	free(double_list);
}

void	ft_double_free_start(char **double_list, int start)
{
	size_t	i;

	i = start;
	while (double_list[i])
	{
		free(double_list[i]);
		i++;
	}
	free(double_list);
}
