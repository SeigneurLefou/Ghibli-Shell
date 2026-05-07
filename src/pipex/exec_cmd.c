/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:46:01 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/07 09:46:24 by lchamard         ###   ########.fr       */
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

char	*test_all_path(char *path, t_cmd *cmd)
{
	char	*cmd_path;
	char	*iter_path;
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
		iter_path = ft_strjoin(splited_path[i++], "/");
		cmd_path = ft_strjoin(iter_path, cmd->name);
		free(iter_path);
		if (!access(cmd_path, X_OK | F_OK))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_double_free(splited_path);
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
		if (!access(cmd_path, X_OK | F_OK))
		{
			cmd->path = cmd_path;
			return ;
		}
	}
	free(cmd_path);
	cmd_path = NULL;
	path = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
				"PATH"));
	cmd_path = test_all_path(path, cmd);
	cmd->path = cmd_path;
}

void	take_child(t_pipex *pipex_var)
{
	char	**env;

	if (pipex_var->fds[0] > 2)
	{
		dup2(pipex_var->fds[0], 0);
		close(pipex_var->fds[0]);
	}
	if (pipex_var->fds[1] > 2)
	{
		dup2(pipex_var->fds[1], 1);
		close(pipex_var->fds[1]);
	}
	if (is_command_built_in(pipex_var->cmd->name))
	{
		exec_builtin(pipex_var->cmd, pipex_var->minishell);
		ft_cmdclear(pipex_var->cmd);
		exit(pipex_var->wstatus);
	}
	else if (pipex_var->cmd->path && pipex_var->fds[0] != -1)
	{
		env = env_variables_manager_get_env_compatible_variables_char_star_star(&pipex_var->minishell->env_variables_manager);
		execve(pipex_var->cmd->path, pipex_var->cmd->argv, env);
	}
	perror(pipex_var->cmd->name);
	ft_cmdclear(pipex_var->cmd);
	exit(2);
}
