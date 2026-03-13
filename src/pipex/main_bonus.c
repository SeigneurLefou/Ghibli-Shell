/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:46:17 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/13 15:36:55 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipex	pipex_loop(int argc, char **argv, char **env)
{
	t_pipex	pipex_var;
	t_cmd	*cmd_save;

	pipex_var.outfile = argv[argc - 1];
	init_pipex_bonus(argc, argv, &pipex_var);
	pipex_var.env = env;
	cmd_save = pipex_var.cmd;
	execution_loop(&pipex_var);
	ft_cmdclear(cmd_save);
	return (pipex_var);
}

int	main(int argc, char **argv, char **env)
{
	int		werror;
	int		exit_code;
	t_pipex	pipex_var;

	if (!argv)
	{
		ft_printf(strerror(EINVAL));
		exit(1);
	}
	pipex_var = pipex_loop(argc, argv, env);
	close(pipex_var.fd[0]);
	werror = wait_all_pid(&pipex_var);
	exit_code = give_exit_code(werror);
	exit(exit_code);
}
