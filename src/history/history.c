/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:08:15 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/01 16:19:03 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

bool	read_file(char *filename)
{
	unsigned int	index;
	char			*line;
	int				fd;
	char			*trimmed;

	index = 0;
	line = (char *)1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Ghiblistory");
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
		trimmed = ft_strtrim(line, " \n\r\t");
		if (!trimmed)
		{
			free(trimmed);
			free(line);
			close(fd);
			return (false);
		}
		add_history(trimmed);
		free(trimmed);
		free(line);
	}
	close(fd);
	return (true);
}

void	load_history_file(t_minishell *minishell, char *filename)
{
	char	*config_path;
	int		fd;

	config_path = get_config_file_path(minishell, filename);
	if (config_path)
	{
		if (!access(config_path, F_OK))
			read_file(config_path);
		else
			fd = open(config_path,  O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	close(fd);
	free(config_path);
}

void	add_to_history_file(t_minishell *minishell, char *filename, char *line)
{
	char	*config_path;
	int		fd;

	config_path = get_config_file_path(minishell, filename);
	if (config_path)
	{
		if (!access(config_path, F_OK))
		{
			fd = open(config_path, O_CREAT | O_WRONLY | O_APPEND, 0644);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		else
			fd = open(config_path,  O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	close(fd);
	free(config_path);
}
