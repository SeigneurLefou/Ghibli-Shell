/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/26 15:57:54 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(int argc, int fds[2])
{
	char	path_buffer[PATH_MAX];

	if (argc < 1)
		return (1);
	if (!getcwd(path_buffer, PATH_MAX))
		perror("Pwd");
	write(fds[1], path_buffer, ft_strlen(path_buffer));
	write(fds[1], "\n", 1);
	return (0);
}
