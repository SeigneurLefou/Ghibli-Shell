/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:34:43 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 18:50:05 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_runner.h"

bool	read_every_line(t_minishell *minishell, char *line, int fd)
{
	char	*trimmed;

	while (line)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			return (false);
		}
		trimmed = ft_strtrim(line, "\r\n \t\v\f");
		if (!trimmed)
			default_error_exit(NULL);
		if (!main_token(trimmed, minishell))
		{
			mem_free(trimmed);
			mem_free(line);
			close(fd);
			return (false);
		}
		mem_free(trimmed);
		mem_free(line);
	}
	return (true);
}

bool	execute_file(char *filename, t_minishell *minishell)
{
	char	*line;
	int		fd;

	line = (char *)1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("GhibliShell");
		return (false);
	}
	if (read_every_line(minishell, line, fd))
		return (false);
	close(fd);
	return (true);
}
