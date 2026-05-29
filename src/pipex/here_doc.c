/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:48:59 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/29 20:46:11 by yben-dje         ###   ########.fr       */
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

static int	get_file_while_not_limiter(int fd, char *limiter, char **buffer)
{
	char			*line;
	unsigned int	limiter_len;

	write(1, "> ", 2);
	limiter_len = ft_strlen(limiter);
	line = get_next_line(fd);
	while (line && limiter && !(!ft_strncmp(line, limiter, limiter_len)
			&& (line[limiter_len] == '\n' || !line[limiter_len])))
	{
		*buffer = ft_strjoin(*buffer, line);
		mem_free(line);
		write(1, "> ", 2);
		line = get_next_line(fd);
	}
	mem_free(line);
	return (0);
}

static bool write_buffer_to_pipe(int		pipe_fd[2], char *limiter, int *fd, t_btree *tree)
{
	char	*input_user;

	setup_sig_handler();
	input_user = ft_calloc(1, sizeof(char));
	if (pipe(pipe_fd) < 0)
	{
		*fd = -1;
		disable_sig_handler();
		tree->minishell->last_status = 127;
		tree->node->wstatus = 127;
		return (false);
	}
	get_file_while_not_limiter(0, limiter, &input_user);
	write(pipe_fd[1], input_user, ft_strlen(input_user));
	close(pipe_fd[1]);
	if (input_user)
		mem_free(input_user);
	return (true);
}

void	here_doc_file(char *limiter, int *fd, t_btree *tree)
{
	int		pipe_fd[2];

	if (!write_buffer_to_pipe(pipe_fd, limiter, fd, tree))
		return ;
	if (*fd > 2)
		close(*fd);
	*fd = pipe_fd[0];
	if (g_signal > 0)
	{
		*fd = -2;
		tree->minishell->last_status = 130;
		tree->node->wstatus = 130;
		close(pipe_fd[0]);
	}
	disable_sig_handler();
}
