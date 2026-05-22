/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 07:57:26 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/22 09:31:09 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_close_fds.h"

int ft_close(int fd, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (fd < 0)
		return (-1);
	while (i < MAX_NUMBER_FDS)
	{
		if (minishell->all_fds[i] == fd)
			minishell->all_fds[i] = 0;
		i++;
	}
	return (close(fd));
}

int ft_close_all(t_minishell *minishell)
{
	int	i;
	int	return_value;

	i = 0;
	while (i < MAX_NUMBER_FDS)
	{
		if (minishell->all_fds[i] > 0)
		{
			if (close(minishell->all_fds[i]) != -1)
				return_value = -1;
			minishell->all_fds[i] = 0;
		}
		i++;
	}
	return (return_value);
}

void show_open_fds(t_minishell *minishell)
{
	int	i;

	i = 0;
	printf("FDS [\n");
	while (i < MAX_NUMBER_FDS)
	{
		if (minishell->all_fds[i] != 0)
			printf("fd : %s\n", ft_itoa(minishell->all_fds[i]));
		i++;
	}
	printf("]\n");
}
