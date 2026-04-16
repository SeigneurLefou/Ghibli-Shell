/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/16 13:22:38 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(int argc, char **argv)
{
	char	path_buffer[PATH_MAX];

	if (argc != 1)
	{
		write(2, "Pwd needs no argument.\n", 24);
		return (1);
	}
	if (!getcwd(path_buffer, PATH_MAX))
		perror("Pwd");
	printf("%s\n", path_buffer);
	return (0);
}
