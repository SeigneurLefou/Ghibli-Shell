/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:37:41 by lchamard          #+#    #+#             */
/*   Updated: 2026/02/12 12:20:35 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*join_line_with_previous_line(char	*buffer, char *line)
{
	size_t	len;
	char	*tmp_line;

	len = 0;
	while (buffer && buffer[len] && buffer[len] != '\n')
		len++;
	tmp_line = ft_strnjoin(line, buffer, ft_strlen(line) + len + 1);
	return (tmp_line);
}

char	*give_next_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	while (buffer && buffer[i] && buffer[i] != '\n')
		i++;
	new_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!new_buffer)
		free(buffer);
	if (!new_buffer)
		return (NULL);
	if (buffer[i])
		i++;
	j = 0;
	while (buffer && buffer[i])
	{
		new_buffer[j] = buffer[i];
		j++;
		i++;
	}
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}

char	*while_no_newline(int fd, char *buffer, char *line)
{
	ssize_t		r;

	while (buffer && !ft_strchr(buffer, '\n'))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r < 0)
		{
			free(line);
			return (NULL);
		}
		if (r == 0)
			return (line);
		buffer[r] = 0;
		line = join_line_with_previous_line(buffer, line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || fd > 1023)
		return (NULL);
	line = NULL;
	if (buffer)
		line = join_line_with_previous_line(buffer, line);
	else
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	line = while_no_newline(fd, buffer, line);
	if (!buffer)
		return (line);
	buffer = give_next_line(buffer);
	if (!buffer[0])
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
