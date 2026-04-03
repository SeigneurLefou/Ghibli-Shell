/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:07:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/02 19:17:41 by yben-dje         ###   ########.fr       */
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
# include "libft.h"
# include "get_next_line.h"
# include "cmd.h"

typedef struct s_pipex
{
	int				fds[3];
	int				*pid;
	int				pid_i;
	char			**env;
	struct s_cmd	*cmd;
}				t_pipex;

int		infile_gestion(t_pipex *pipex_var);
int		here_doc_file(char *limiter);
int		get_file_while_not_limiter(int fd, char *limiter, char **buffer);
int		pipe_gestion(t_pipex *pipex_var);
int		child_gestion(t_pipex *pipex_var);
int		fork_pid(t_pipex	*pipex_var, char *cmd_path);
int		execution_loop(t_pipex *pipex_var);
int		infile_gestion(t_pipex *pipex_var);
int		pipe_gestion(t_pipex *pipex_var);
int		child_gestion(t_pipex *pipex_var);
int		fork_pid(t_pipex	*pipex_var, char *cmd_path);
void	take_child(t_pipex *pipex_var, char *cmd_path);
char	*get_cmd_path(t_pipex *pipex_var);
char	*test_all_path(char *path, t_pipex *pipex_var);
void	ft_free_path(char **splited_path, int i);
char	*get_env(t_pipex *pipex_var, char *var);
int		wait_all_pid(t_pipex *pipex_var);
int		give_exit_code(int status);
int		fake_fdin(void);

#endif
