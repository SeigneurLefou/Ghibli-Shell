/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:46:01 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/08 09:50:19 by lchamard         ###   ########.fr       */
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
	while (env[i]
		&& ft_strncmp(env[i], var, len_var_name))
		i++;
	if (!env[i])
		return (NULL);
	var_content = ft_calloc(sizeof(char), ft_strlen(env[i])
			- len_var_name);
	var_content = ft_strcpy(var_content, &env[i][len_var_name + 1]);
	return (var_content);
}

void	ft_free_path(char **splited_path, int i)
{
	if (splited_path && !splited_path[i])
	{
		free(splited_path);
		return ;
	}
	ft_double_free_start(splited_path, i);
}

char	*test_all_path(char *path, t_cmd **cmd)
{
	char	*cmd_path;
	char	**splited_path;
	int		i;

	if (!path || !path[0])
	{
		free(path);
		return (NULL);
	}
	splited_path = ft_split(path, ':');
	free(path);
	i = 0;
	cmd_path = NULL;
	while (splited_path && splited_path[i])
	{
		cmd_path = ft_strjoin(splited_path[i++], "/");
		cmd_path = ft_strjoin(cmd_path, (*cmd)->name);
		if (!access(cmd_path, X_OK | F_OK))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_free_path(splited_path, i);
	return (cmd_path);
}

void	get_cmd_path(t_cmd **cmd, char **env)
{
	char	*path;
	char	*cmd_path;

	if (!(*cmd)->name)
	{
		errno = 13;
		(*cmd)->path = NULL;
		return ;
	}
	cmd_path = ft_strdup((*cmd)->name);
	if (cmd_path && ft_strchr(cmd_path, '/'))
	{
		if (!access(cmd_path, X_OK | F_OK))
		{
			(*cmd)->path = cmd_path;
			return ;
		}
	}
	free(cmd_path);
	cmd_path = NULL;
	path = get_env(env, "PATH");
	cmd_path = test_all_path(path, cmd);
	(*cmd)->path = cmd_path;
}

void	take_child(t_pipex *pipex_var)
{
	dup2(pipex_var->fds[0], 0);
	if (pipex_var->fds[0] != 0)
		close(pipex_var->fds[0]);
	dup2(pipex_var->fds[1], 1);
	if (pipex_var->fds[1] != 1)
		close(pipex_var->fds[1]);
	if (pipex_var->cmd->path && pipex_var->fds[0] != -1)
		execve(pipex_var->cmd->path, pipex_var->cmd->argv, pipex_var->env);
	ft_cmdclear(pipex_var->cmd);
	exit(2);
}
