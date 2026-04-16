/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:34:43 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/17 00:50:06 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_runner.h"


bool execute_file(char *filename, char *env[])
{
	unsigned int index;
	char *line;
	int fd;
	char *trimmed;

	index = 0;
	line = (char *)1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		display_error_message("Failed to open the file.");
		return (false);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			{
				if (fd > 2)
					close(fd);
				return (false);
			}
		if (line)
		{
			trimmed = ft_strtrim(line, "\r\n \t");
			if (!trimmed || !main_token(trimmed, env))
			{
				free(trimmed);
				free(line);
				if (fd > 2)
					close(fd);
				return (false);
			}
			free(trimmed);
		}
		free(line);
	}
	if (fd > 2)
		close(fd);
	return (true);
}
