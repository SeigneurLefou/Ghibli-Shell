/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:24:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/19 11:23:49 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	open_file(char *file_name, int open_mode, int *fd)
{
	if (*fd > 2)
		close(*fd);
	// VERIFY FILE WITH ACCESS OR STAT
	*fd = open(file_name, open_mode, 0644);
	if (*fd < 0)
		return (false);
	return (true);
}

bool	open_io_fds(t_btree	*tree, int fds[2])
{
	size_t		i;
	t_io_file	*io_file;
	char		*file_name;

	i = 0;
	while (i < tree->node->io_files.size)
	{
		io_file = vec_get(&tree->node->io_files, i);
		file_name = vec_to_cstring(vec_get(&tree->expr,
					io_file->file_name_token_index));
		if (io_file->type == io_type_infile)
			open_file(file_name, O_RDONLY, &fds[0]);
		else if (io_file->type == io_type_heredoc)
			here_doc_file(file_name, &fds[0]);
		else if (io_file->type == io_type_outfile)
			open_file(file_name, O_CREAT | O_WRONLY | O_TRUNC, &fds[1]);
		else if (io_file->type == io_type_append_file)
			open_file(file_name, O_CREAT | O_WRONLY | O_APPEND, &fds[1]);
		if (fds[0] < 0 || fds[1] < 0)
			return (false);
		i++;
		printf("filename %s\n", file_name);
		printf("files 0 : %d, files 1 : %d\n", fds[0], fds[1]);
		free(file_name);
	}
	printf("%zu io files\n", i);
	return (true);
}

void	close_new_files(int *old_files, int *new_files)
{
	if (new_files[0] > 2 && old_files[0] != new_files[0])
		close(new_files[0]);
	if (new_files[1] > 2 && old_files[1] != new_files[1])
		close(new_files[1]);
}
