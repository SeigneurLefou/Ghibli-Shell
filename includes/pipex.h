/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:58:09 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/07 09:46:44 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "btree.h"
# include "libft.h"
# include "get_next_line.h"
# include "cmd.h"
# include "builtin.h"
# include "minishell.h"

typedef struct s_minishell	t_minishell;
typedef struct s_btree_node	t_btree_node;
typedef struct s_btree		t_btree;

typedef struct s_pipex
{
	int				fds[2];
	int				pid;
	t_minishell		*minishell;
	struct s_cmd	*cmd;
	int				wstatus;
}				t_pipex;

int		here_doc_file(char *limiter);
int		get_file_while_not_limiter(int fd, char *limiter, char **buffer);
int		pipe_gestion(t_pipex *pipex_var);
int		fork_pid(t_pipex *pipex_var);
int		infile_gestion(t_pipex *pipex_var);
int		pipe_gestion(t_pipex *pipex_var);
int		child_gestion(t_pipex *pipex_var);
void	take_child(t_pipex *pipex_var);
void	get_cmd_path(t_cmd *cmd, t_minishell *minishell);
char	*test_all_path(char *path, t_cmd *cmd);
void	ft_free_path(char **splited_path, int i);
char	*get_env(char **env, char *var);
int		wait_all_pid(t_vec *pids);
int		give_exit_code(int status);
int		fake_fdin(void);
void	open_file(char *file_name, int open_mode, int *fd);
void	open_io_fds(t_btree *tree, int *fds);

#endif
