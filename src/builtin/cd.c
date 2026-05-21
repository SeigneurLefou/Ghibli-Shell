/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/18 20:39:48 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int go_home(t_minishell *minishell)
{
	char	*home;

	home = env_variables_get(&minishell->env_variables_manager, "HOME");
	if (home)
	{
		if (chdir(home))
		{
			perror("CD");
			return (127);
		}
	}
	return (0);
}

bool update_pwd(t_minishell *minishell)
{
	char	path_buffer[PATH_MAX];

	if (!getcwd(path_buffer, PATH_MAX))
	{
		perror("CD");
		return (false);
	}
	env_variables_set(&minishell->env_variables_manager, "PWD", path_buffer);
	env_variables_set(&minishell->env_variables_manager, "OLDPWD", path_buffer);
	return (true);
}

int	builtin_cd(int argc, char **argv, t_minishell *minishell)
{
	if (argc > 2)
	{
		write(2, "Too much arguments.\n", 21);
		return (1);
	}
	if (argc == 1)
	{
		int result = go_home(minishell);
		if (result)
			return (result);
	}
	else
	{
		if (chdir(argv[1]))
		{
			perror("CD");
			return (127);
		}
	}
	if (!update_pwd(minishell))
		return (1);
	return (0);
}
