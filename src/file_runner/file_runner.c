/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:34:43 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/05 10:12:44 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_runner.h"


bool execute_file(char *filename, t_minishell *minishell)
{
	char *line;
	int fd;
	char *trimmed;

	line = (char *)1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("GhibliShell");
		return (false);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return (false);
		}
		trimmed = ft_strtrim(line, "\r\n \t");
		if (!trimmed || !main_token(trimmed, minishell))
		{
			free(trimmed);
			free(line);
			close(fd);
			return (false);
		}
		free(trimmed);
		free(line);
	}
	if (fd > 2)
		close(fd);
	return (true);
}
