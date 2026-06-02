/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:07:06 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/02 13:06:24 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exits.h"
#include "error_manager.h"
#include <unistd.h>
#include <sys/stat.h>

void	close_all_fds(void)
{
	struct stat		buf;
	unsigned int	index;

	index = 3;
	while (index < 1024)
	{
		if (fstat(index, &buf) != -1)
			close(index);
		index++;
	}
}

void	memory_allocation_failed_error_exit(void)
{
	display_error_message("Memory allocation failed!");
	rl_clear_history();
	close_all_fds();
	exit(1);
}

void	default_error_exit(void *data)
{
	(void)data;
	memory_allocation_failed_error_exit();
}
