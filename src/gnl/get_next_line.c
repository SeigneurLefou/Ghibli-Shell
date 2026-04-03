/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:28:20 by yben-dje          #+#    #+#             */
/*   Updated: 2025/12/04 19:43:12 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	take_remaining(char **str, int index, char **line)
{
	int		remaining_index;
	char	*remaining;

	remaining_index = 0;
	while ((*str)[remaining_index + index])
		remaining_index++;
	remaining = malloc(remaining_index + 1);
	if (!remaining)
	{
		safe_free(line);
		safe_free(str);
		return (0);
	}
	remaining[remaining_index] = 0;
	remaining_index = 0;
	while ((*str)[index])
		remaining[remaining_index++] = (*str)[index++];
	safe_free(str);
	*str = remaining;
	return (1);
}

char	*take_line(char **str)
{
	int		size;
	int		index;
	char	*line;

	size = 0;
	while ((*str)[size] && (*str)[size] != '\n')
		size++;
	line = malloc(size + 1 + ((*str)[size] == '\n'));
	if (!line)
	{
		safe_free(str);
		return (NULL);
	}
	line[size + ((*str)[size] == '\n')] = 0;
	index = -1;
	while (++index <= size)
		line[index] = (*str)[index];
	if (!(*str)[index - 1])
	{
		safe_free(str);
		return (line);
	}
	if (!take_remaining(str, index, &line))
		return (NULL);
	return (line);
}

int	read_lines(char **stach, int fd, char **buf, char **line)
{
	int	result;

	while (!contains(*stach, '\n') || !*stach || !(*stach)[0])
	{
		result = read(fd, *buf, BUFFER_SIZE);
		if (result > 0)
			(*buf)[result] = 0;
		if (!result && *stach && (*stach)[0])
			break ;
		if (result <= 0)
		{
			safe_free(stach);
			safe_free(buf);
			return (0);
		}
		(*stach) = gnl_strjoin(*stach, *buf, result);
		if (!*stach)
		{
			safe_free(buf);
			safe_free(line);
			return (0);
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*stach[1024];
	char		*line;

	if (fd < 0 || fd > 1023)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = NULL;
	if (!read_lines(stach + fd, fd, &buf, &line))
		return (NULL);
	line = take_line(stach + fd);
	if (stach[fd] && !stach[fd][0])
		safe_free(stach + fd);
	free(buf);
	return (line);
}
