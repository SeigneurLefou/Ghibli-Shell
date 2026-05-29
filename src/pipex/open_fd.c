/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:24:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/29 20:41:03 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	open_file(char *file_name, int open_mode, int *fd, t_btree *tree)
{
	if (*fd > 2)
		close(*fd);
	*fd = open(file_name, open_mode, 0644);
	if (*fd < 0)
	{
		tree->minishell->last_status = 1;
		tree->node->wstatus = 1;
		perror("GhibliShell");
		return (false);
	}
	return (true);
}

static char	*get_expanded_io_file_name(t_btree *tree, t_io_file *io_file)
{
	char	*file_name;
	t_vec	expanded;

	vec_init(&expanded, sizeof(t_token), 2);
	expand(&expanded, vec_get(&tree->expr, io_file->file_name_token_index),
		tree->minishell);
	if (expanded.size != 1)
	{
		display_error_message("Ambiguous IO file.");
		tree->minishell->last_status = 1;
		tree->node->wstatus = 1;
		vec_free(&expanded);
		return (NULL);
	}
	file_name = vec_to_cstring(vec_get(&expanded, 0));
	return (file_name);
}

bool	open_io_fds(t_btree *tree, int fds[2])
{
	size_t		i;
	t_io_file	*io_file;
	char		*file_name;

	i = 0;
	while (i < tree->node->io_files.size)
	{
		io_file = vec_get(&tree->node->io_files, i);
		file_name = get_expanded_io_file_name(tree, io_file);
		if (!file_name)
			return (false);
		if (io_file->type == io_type_infile)
			open_file(file_name, O_RDONLY, &fds[0], tree);
		else if (io_file->type == io_type_heredoc)
			here_doc_file(file_name, &fds[0], tree);
		else if (io_file->type == io_type_outfile)
			open_file(file_name, O_CREAT | O_WRONLY | O_TRUNC, &fds[1], tree);
		else if (io_file->type == io_type_append_file)
			open_file(file_name, O_CREAT | O_WRONLY | O_APPEND, &fds[1], tree);
		if (fds[0] < 0 || fds[1] < 0)
			return (false);
		i++;
		mem_free(file_name);
	}
	return (true);
}

void	close_new_files(int *old_files, int *new_files)
{
	if (new_files[0] > 2 && old_files[0] != new_files[0])
		close(new_files[0]);
	if (new_files[1] > 2 && old_files[1] != new_files[1])
		close(new_files[1]);
}

void	close_files_if_open(int *files)
{
	if (files[0] > 2)
		close(files[0]);
	if (files[1] > 2)
		close(files[1]);
}
