/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/23 19:15:54 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_cd(int argc, char **argv, t_minishell *minishell)
{
	char	path_buffer[PATH_MAX];
	char	*home;

	if (argc > 2)
	{
		write(2, "Too much arguments.\n", 21);
		return (1);
	}
	if (argc == 1)
	{
		home = env_variable_manager_get_single(&minishell->env_variables_manager,
				"HOME");
		if (home)
		{
			if (!chdir(home))
				perror("CD");
		}
	}
	else
	{
		if (!chdir(argv[1]))
			perror("CD");
	}
	if (!getcwd(path_buffer, PATH_MAX))
		perror("CD");
	env_variable_manager_set(&minishell->env_variables_manager, "PWD",
		path_buffer);
	env_variable_manager_set(&minishell->env_variables_manager, "OLDPWD",
		path_buffer);
	return (0);
}
