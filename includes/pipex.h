/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:07:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/13 15:11:18 by lchamard         ###   ########.fr       */
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

typedef struct s_pipex
{
	int				fdio[3];
	int				*pid;
	int				pid_i;
	char			**env;
	struct s_cmd	*cmd;
}				t_pipex;

void	exec_cmd(t_pipex *pipex_var, char *path_cmd);
void	take_child(t_pipex *pipex_var, char *path_cmd);
int		fork_pid(t_pipex	*pipex_var, char *path_cmd);
char	*get_env(t_pipex *pipex_var, char *var);
char	*get_cmd_path(t_pipex *pipex_var);
int		get_file_while_not_limiter(int fd, char *limiter, char **buffer);
int		here_doc_file(char **argv);
int		give_exit_code(int status);
int		wait_all_pid(t_pipex *pipex_var);
int		fake_fdin(void);
// t_cmd	*init_list_cmd(int argc, char **argv);
// void	init_pipex(int argc, char **argv, t_pipex *pipex_var);
int		execution_loop(t_pipex *pipex_var);
//int		execution_loop_here_doc(t_pipex *pipex_var);
int		pipe_gestion(t_pipex *pipex_var, int open_flag);

#endif
