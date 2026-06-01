/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:58:09 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/01 14:33:04 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "btree.h"
# include "builtin.h"
# include "cmd.h"
# include "get_next_line.h"
# include "libft.h"
# include "minishell.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_minishell	t_minishell;
typedef struct s_btree_node	t_btree_node;
typedef struct s_btree		t_btree;

typedef struct s_pipex
{
	int						fds[2];
	int						pid;
	t_minishell				*minishell;
	struct s_cmd			*cmd;
	int						wstatus;
}							t_pipex;

void	here_doc_file(char *limiter, int *fd, t_btree *tree);
int		pipe_gestion(t_pipex *pipex_var);
int		fork_pid(t_pipex *pipex_var, int stdin_pid_copy);
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
bool	open_file(char *file_name, int open_mode, int *fd, t_btree *tree);
bool	open_io_fds(t_btree *tree, int fds[2]);
void	close_new_files(int *old_files, int *new_files);
void	close_files_if_open(int *files);

#endif
