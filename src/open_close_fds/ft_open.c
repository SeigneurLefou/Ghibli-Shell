/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 07:52:44 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/22 10:06:40 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_close_fds.h"

static bool	append_fd(int fd, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (fd < 0)
		return (false);
	while (minishell->all_fds[i] != 0 && i < MAX_NUMBER_FDS)
		i++;
	if (i >= MAX_NUMBER_FDS)
	{
		close(fd);
		return (false);
	}
	minishell->all_fds[i] = fd;
	return (true);
}

int	ft_open(const char *pathname, int flags, t_minishell *minishell)
{
	int	fd;

	fd = open(pathname, flags);
	if (fd < 0)
		return (fd);
	if (append_fd(fd, minishell))
		return (-1);
	return (fd);
}

int	ft_open_mode(const char *pathname, int flags,
			mode_t mode, t_minishell *minishell)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd < 0)
		return (fd);
	if (!append_fd(fd, minishell))
		return (-1);
	return (fd);
}

int	ft_pipe(int pipefd[2], t_minishell *minishell)
{
	int	return_value;

	return_value = pipe(pipefd);
	if (!append_fd(pipefd[0], minishell) || !append_fd(pipefd[1], minishell))
		return (-1);
	return (0);
}
