/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:48:59 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/03 13:51:54 by yben-dje         ###   ########.fr       */
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

static unsigned int	get_variable_name_len(char *start)
{
	unsigned int	size;

	size = 0;
	while (is_valid_expand_char(start[size]))
		size++;
	return (size);
}

static char	*get_variable_content(char *start, t_minishell *minishell)
{
	char			*name;
	unsigned int	index;
	char			*value;
	unsigned int	size;

	size = get_variable_name_len(start);
	name = mem_alloc(size + 1, default_error_exit, NULL, 0b1);
	name[size] = 0;
	index = 0;
	while (index < size)
	{
		name[index] = start[index];
		index++;
	}
	value = env_variables_get(&minishell->env_variables_manager, name);
	return (value);
}

static void add_expand(unsigned int *index, char *line, t_vec *expanded, t_minishell *minishell)
{
	(*index)++;
	char *data = get_variable_content(line + (*index), minishell);
	if (data)
		vec_expand_from_str(expanded, data);
	(*index) += get_variable_name_len(line + (*index));
}

char	*expand_str(char *line, t_minishell *minishell)
{
	t_vec			expanded;
	unsigned int	index;
	unsigned int	line_size;
	
	line_size = ft_strlen(line);
	vec_init(&expanded, sizeof(char), 10);
	index = 0;
	while (index < line_size)
	{
		if (line[index] == '\\' && line[index + 1] == '$')
		{
			vec_append(&expanded, "$");
			index += 2;
		}
		else if (line[index] == '$' && is_valid_expand_char(line[index + 1]))
			add_expand(&index, line, &expanded, minishell);
		else
			vec_append(&expanded, &line[index++]);
	}
	char *data = vec_to_cstring(&expanded);
	vec_free(&expanded);
	return(data);
}

static char *get_file_while_not_limiter(int fd, char *limiter, t_minishell *minishell, bool can_expand)
{
	char			*line;
	unsigned int	limiter_len;
	char *buffer;

	buffer = ft_calloc(1, sizeof(char));
	write(2, "> ", 2);
	limiter_len = ft_strlen(limiter);
	line = get_next_line(fd);
	while (line && limiter && !(!ft_strncmp(line, limiter, limiter_len)
			&& (line[limiter_len] == '\n' || !line[limiter_len])))
	{
		if (can_expand)
		{
			char *expanded = expand_str(line, minishell);
			buffer = ft_strjoin(buffer, expanded);
			mem_free(expanded);
		}
		else
			buffer = ft_strjoin(buffer, line);
		mem_free(line);
		write(2, "> ", 2);
		line = get_next_line(fd);
	}
	mem_free(line);
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
	input_user = get_file_while_not_limiter(0, limiter, tree->minishell, can_expand);
	write(pipe_fd[1], input_user, ft_strlen(input_user));
	close(pipe_fd[1]);
	if (input_user)
		mem_free(input_user);
	return (true);
}

void	here_doc_file(char *limiter, int *fd, t_btree *tree, unsigned int token_index)
{
	int	pipe_fd[2];
	bool can_expand;

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
		write(1, "\n", 1);
		close(pipe_fd[0]);
	}
	disable_sig_handler();
}
