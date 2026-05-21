/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:48:59 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/21 19:01:30 by yben-dje         ###   ########.fr       */
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
		mem_free(line);
		line = get_next_line(fd);
	}
	mem_free(line);
	return (0);
}

void	here_doc_file(char *limiter, int *fd)
{
	int		pipe_fd[2];
	char	*input_user;
	char	*limiter_with_enter;

	limiter_with_enter = ft_strjoin(limiter, "\n");
	input_user = ft_calloc(1, sizeof(char));
	pipe(pipe_fd);
	get_file_while_not_limiter(0, limiter_with_enter, &input_user);
	write(pipe_fd[1], input_user, ft_strlen(input_user));
	close(pipe_fd[1]);
	if (input_user)
		mem_free(input_user);
	mem_free(limiter_with_enter);
	if (*fd > 2)
		close(*fd);
	*fd = pipe_fd[0];
}
