/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:48:59 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/05 17:10:32 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	append_to_buffer(char **buffer, char *line, t_minishell *minishell)
{
	char	*expanded;

	expanded = expand_str(line, minishell);
	*buffer = ft_strjoin(*buffer, expanded);
	mem_free(expanded);
}

static char	*get_file_while_not_limiter(int fd, char *limiter,
		t_minishell *minishell, bool can_expand)
{
	char			*line;
	unsigned int	limiter_len;
	char			*buffer;

	buffer = ft_calloc(1, sizeof(char));
	write(2, "> ", 2);
	limiter_len = ft_strlen(limiter);
	line = get_next_line(fd);
	while (line && limiter && !(!ft_strncmp(line, limiter, limiter_len)
			&& (line[limiter_len] == '\n' || !line[limiter_len])))
	{
		if (can_expand)
			append_to_buffer(&buffer, line, minishell);
		else
			buffer = ft_strjoin(buffer, line);
		mem_free(line);
		write(2, "> ", 2);
		line = get_next_line(fd);
	}
	mem_free(line);
	if (!line)
		write(2, "\n", 1);
	return (buffer);
}

static bool	write_buffer_to_pipe(int pipe_fd[2], char *limiter, bool can_expand,
		t_btree *tree)
{
	char	*input_user;

	setup_sig_handler();
	input_user = ft_calloc(1, sizeof(char));
	if (pipe(pipe_fd) < 0)
	{
		disable_sig_handler();
		tree->minishell->last_status = 127;
		tree->node->wstatus = 127;
		return (false);
	}
	input_user = get_file_while_not_limiter(0, limiter, tree->minishell,
			can_expand);
	write(pipe_fd[1], input_user, ft_strlen(input_user));
	close(pipe_fd[1]);
	if (input_user)
		mem_free(input_user);
	return (true);
}

void	here_doc_file(char *limiter, int *fd, t_btree *tree,
		unsigned int token_index)
{
	int		pipe_fd[2];
	bool	can_expand;

	can_expand = !((t_token *)vec_get(&tree->expr, token_index))->no_skip;
	if (!write_buffer_to_pipe(pipe_fd, limiter, can_expand, tree))
	{
		*fd = -1;
		return ;
	}
	if (*fd > 2)
		close(*fd);
	*fd = pipe_fd[0];
	if (g_signal > 0)
	{
		*fd = -2;
		tree->minishell->last_status = 130;
		tree->node->wstatus = 130;
		write(2, "\n", 1);
		close(pipe_fd[0]);
	}
	disable_sig_handler();
}
