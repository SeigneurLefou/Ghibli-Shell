/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:46:17 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/05 08:13:20 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		werror;
	int		exit_code;
	t_pipex	pipex_var;
	t_cmd	*tmp;

	if (argc != 5 || !ft_strcmp("here_doc", argv[1]) || !env)
	{
		ft_printf(strerror(EINVAL));
		exit(0);
	}
	pipex_var.outfile = argv[argc - 1];
	init_pipex(argc, argv, &pipex_var);
	pipex_var.env = env;
	tmp = pipex_var.cmd;
	execution_loop(&pipex_var);
	close(pipex_var.fd[0]);
	ft_cmdclear(tmp);
	werror = wait_all_pid(&pipex_var);
	exit_code = give_exit_code(werror);
	exit(exit_code);
}
