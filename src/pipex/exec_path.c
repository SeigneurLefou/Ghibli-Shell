/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:20:36 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 20:21:00 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char **env, char *var)
{
	int		i;
	int		len_var_name;
	char	*var_content;

	i = 0;
	len_var_name = ft_strlen(var);
	while (env[i] && ft_strncmp(env[i], var, len_var_name))
		i++;
	if (!env[i])
		return (NULL);
	var_content = ft_calloc(sizeof(char), ft_strlen(env[i]) - len_var_name);
	var_content = ft_strcpy(var_content, &env[i][len_var_name + 1]);
	return (var_content);
}

char	*test_all_path(char *path, t_cmd *cmd)
{
	char	*cmd_path;
	char	**splited_path;
	int		i;

	if (!path || !path[0])
		return (NULL);
	splited_path = ft_split(path, ':');
	i = 0;
	cmd_path = NULL;
	while (splited_path && splited_path[i])
	{
		cmd_path = path_join(splited_path[i++], cmd->name);
		if (!access(cmd_path, F_OK))
			break ;
		mem_free(cmd_path);
		cmd_path = NULL;
	}
	ft_double_mem_free(splited_path);
	return (cmd_path);
}

void	get_cmd_path(t_cmd *cmd, t_minishell *minishell)
{
	char	*path;
	char	*cmd_path;

	if (!cmd->name)
	{
		errno = 13;
		cmd->path = NULL;
		return ;
	}
	cmd_path = ft_strdup(cmd->name);
	if (cmd_path && ft_strchr(cmd_path, '/'))
	{
		cmd->path = cmd_path;
		return ;
	}
	mem_free(cmd_path);
	cmd_path = NULL;
	path = env_variables_get(&minishell->env_variables_manager, "PATH");
	if (!path)
		cmd->path = NULL;
	if (!path)
		return ;
	cmd_path = test_all_path(path, cmd);
	cmd->path = cmd_path;
}
