/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:24:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/25 08:12:03 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_file(char *file_name, int open_mode, int *fd)
{
	if (*fd)
		close(*fd);
	*fd = open(file_name, open_mode, 0644);
}

void	open_io_fds(t_btree_node node, int *fds[2], t_vec *expr)
{
	int			i;
	t_io_files	io_file;

	i = 0;
	while (i < node->io_files->size)
	{
		io_file = vec_get(node->io_files, i);
		if (io_file->type == io_type_infile)
			open_file(vec_get(expr, node->file_name_token_index), 0_RDONLY, fds[0]);
		else if (io_file->type == io_type_infile)
			(*fds)[0] = here_doc_file(vec_get(expr, node->file_name_token_index));
		else if (io_file->type == io_type_outfile)
			open_file(vec_get(expr, node->file_name_token_index), O_CREAT | O_WRONLY | O_TRUNC, fds[1]);
		else if (io_file->type == io_type_append_file)
			open_file(vec_get(expr, node->file_name_token_index), O_CREAT | O_WRONLY | O_APPEND, fds[1]);
		i++;
	}
}
