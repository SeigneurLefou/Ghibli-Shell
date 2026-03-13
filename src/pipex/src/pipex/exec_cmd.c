/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:46:01 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/05 08:30:41 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(t_pipex *pipex_var, char *var)
{
	int		i;
	int		len_var_name;
	char	*var_content;

	i = 0;
	len_var_name = ft_strlen(var);
	while (pipex_var->env[i]
		&& ft_strncmp(pipex_var->env[i], var, len_var_name))
		i++;
	if (!pipex_var->env[i])
		return (NULL);
	var_content = ft_calloc(sizeof(char), ft_strlen(pipex_var->env[i])
			- len_var_name);
	var_content = ft_strcpy(var_content, &pipex_var->env[i][len_var_name + 1]);
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

char	*test_all_path(char *path, t_pipex *pipex_var)
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
		cmd_path = ft_strjoin(cmd_path, pipex_var->cmd->cmd_name);
		if (!access(cmd_path, X_OK | F_OK))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_free_path(splited_path, i);
	return (cmd_path);
}

char	*get_cmd_path(t_pipex *pipex_var)
{
	char	*path;
	char	*cmd_path;

	if (!pipex_var->cmd->cmd_name)
	{
		errno = 13;
		return (NULL);
	}
	cmd_path = ft_strdup(pipex_var->cmd->cmd_name);
	if (cmd_path && ft_strchr(cmd_path, '/'))
	{
		if (!access(cmd_path, X_OK | F_OK))
			return (cmd_path);
	}
	free(cmd_path);
	cmd_path = NULL;
	path = get_env(pipex_var, "PATH");
	cmd_path = test_all_path(path, pipex_var);
	return (cmd_path);
}

void	take_child(t_pipex *pipex_var, char *cmd_path)
{
	dup2(pipex_var->fd[0], 0);
	close(pipex_var->fd[0]);
	dup2(pipex_var->fd[2], 1);
	close(pipex_var->fd[2]);
	close(pipex_var->fd[1]);
	if (cmd_path && !(pipex_var->fd[0] == -1 && !pipex_var->cmd->previous))
		execve(cmd_path, pipex_var->cmd->cmd_argv, pipex_var->env);
	if (cmd_path)
		free(cmd_path);
	free(pipex_var->pid);
	ft_cmdclear(pipex_var->cmd);
	exit(2);
}
