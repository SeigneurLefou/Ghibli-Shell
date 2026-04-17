/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/17 19:24:53 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_cd(int argc, char **argv, t_env_variables_manager *env_manager)
{
	char	path_buffer[PATH_MAX];

	if (argc != 2)
	{
		write(2, "CD needs one argument <path>.", 30);
		return (1);
	}
	if (!chdir(argv[1]))
		perror("CD");
    if (!getcwd(path_buffer, PATH_MAX))
		perror("CD");
    env_variable_manager_set(env_manager, "PWD", path_buffer);
    env_variable_manager_set(env_manager, "OLDPWD", path_buffer);
	return (0);
}
