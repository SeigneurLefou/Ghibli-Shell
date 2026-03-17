/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:48:59 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 09:52:15 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fake_fdin(void)
{
	int	fake_pipe[2];

	pipe(fake_pipe);
	close(fake_pipe[1]);
	return (fake_pipe[0]);
}

int	get_file_while_not_limiter(int fd, char *limiter, char **buffer)
{
	char	*line;

	line = get_next_line(fd);
	while (line && limiter
		&& ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		*buffer = ft_strjoin(*buffer, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}

int	here_doc_file(char *limiter)
{
	int		pipe_fd[2];
	char	*input_user;
	char	*limiter_with_enter;

	limiter_with_enter = ft_strjoin(limiter, "\n");
	input_user = NULL;
	pipe(pipe_fd);
	get_file_while_not_limiter(0, limiter_with_enter, &input_user);
	write(pipe_fd[1], input_user, ft_strlen(input_user));
	close(pipe_fd[1]);
	if (input_user)
		free(input_user);
	free(limiter_with_enter);
	return (pipe_fd[0]);
}
