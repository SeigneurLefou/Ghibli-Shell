/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:53:44 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/13 16:07:42 by lchamard         ###   ########.fr       */
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

t_cmd	*init_list_cmd(int argc, char **argv)
{
	int		i;
	t_cmd	*cmd;
	t_cmd	*new;

	i = 1;
	cmd = ft_cmdnew(argv[0], 0);
	while (i < argc)
	{
		new = ft_cmdnew(argv[i], i);
		ft_cmdadd_back(&cmd, &new);
		i++;
	}
	return (cmd);
}

void	init_pipex(int argc, char **argv, t_pipex *pipex_var)
{
	int	number_move_right_argv;

	number_move_right_argv = 2;
	if ((argc < 2 && !ft_strcmp(argv[0], "<<"))
		|| (argc < 3 && !ft_strcmp(argv[1], "<<")))
	{
		number_move_right_argv = 3;
		pipex_var->fd[0] = here_doc_file(argv);
	}
	else if ((argc < 2 && !ft_strcmp(argv[0], "<"))
		|| (argc < 3 && !ft_strcmp(argv[1], "<")))
	{
		number_move_right_argv = 2;
		pipex_var->fd[0] = open(argv[1], O_RDONLY);
		if (errno)
			perror(argv[1]);
	}
	if (pipex_var->fd[0] == -1)
	{
		pipex_var->fd[0] = fake_fdin();
		number_move_right_argv++;
	}
	pipex_var->cmd = init_list_cmd(argc - (number_move_right_argv + 1),
			argv + number_move_right_argv);
	pipex_var->pid = ft_calloc(sizeof(int), argc
			- (number_move_right_argv + 1));
	pipex_var->pid_i = 0;
}
