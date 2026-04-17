/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_runner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:34:43 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/17 10:17:08 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_runner.h"


bool execute_file(char *filename, t_minishell *minishell)
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
			return (false);
		if (line)
		{
			trimmed = ft_strtrim(line, "\r\n \t");
			if (!trimmed || !main_token(trimmed, minishell))
			{
				free(trimmed);
				free(line);
				return (false);
			}
		}
		free(line);
	}
	if (fd > 2)
		close(fd);
	return (true);
}
