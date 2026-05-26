/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/26 12:04:33 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	go_home(t_minishell *minishell)
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
	else
	{
		write(2, "CD: HOME is not set.\n", 22);
		return (1);
	}
	return (0);
}

static bool	update_pwd(t_minishell *minishell)
{
	char	path_buffer[PATH_MAX];

	if (!getcwd(path_buffer, PATH_MAX))
	{
		perror("CD");
		return (false);
	}
	if (!env_variables_set(&minishell->env_variables_manager, "PWD", path_buffer))
		return (false);
	return (true);
}

/* The behavior of OLDPWD seems undefined in bash when PWD is unset. */
bool set_old_pwd(t_minishell *minishell)
{
	char	*old_pwd;

	old_pwd = env_variables_get(&minishell->env_variables_manager, "PWD");
	if (old_pwd)
	{	
		if (!env_variables_set(&minishell->env_variables_manager, "OLDPWD", old_pwd))
			return (false);
	}
	else
		env_variables_unset_key(&minishell->env_variables_manager, "OLDPWD");
	return (true);
}

int	builtin_cd(int argc, char **argv, t_minishell *minishell)
{
	int result;

	if (argc > 2)
	{
		write(2, "Too much arguments.\n", 21);
		return (1);
	}
	if (argc == 1)
	{
		result = go_home(minishell);
		if (result)
			return (result);
	}
	else
	{
		set_old_pwd(minishell);
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
