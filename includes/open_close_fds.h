/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close_fds.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:43:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/22 10:06:51 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_CLOSE_FDS_H
# define OPEN_CLOSE_FDS_H

# include "btree.h"
# include "libft.h"
# include "minishell.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_minishell	t_minishell;
typedef struct s_btree_node	t_btree_node;
typedef struct s_btree		t_btree;

int	ft_open(const char *pathname, int flags, t_minishell *minishell);
int	ft_open_mode(const char *pathname, int flags,
			mode_t mode, t_minishell *minishell);
int	ft_pipe(int pipefd[2], t_minishell *minishell);

int ft_close(int fd, t_minishell *minishell);
int ft_close_all(t_minishell *minishell);

void show_open_fds(t_minishell *minishell);

bool	open_file(char *file_name, int open_mode, int *fd,
			t_minishell *minishell);
bool	open_io_fds(t_btree *tree, int fds[2], t_minishell *minishell);
void	close_new_files(int *old_files, int *new_files, t_minishell *minishell);

#endif
