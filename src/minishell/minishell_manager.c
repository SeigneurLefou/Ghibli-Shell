/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:57:17 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 17:57:19 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_init(t_minishell *minishell)
{
	minishell->env_variables_manager = env_variables_new();
	minishell->shell_level = 1;
	minishell->internal_file_recursion = 0;
	minishell->request_exit = false;
}

void	increment_shell_lvl(t_minishell *minishell)
{
	char	*shell_lvl;
	int		shell_lvl_num;

	shell_lvl = env_variables_get(&minishell->env_variables_manager, "SHLVL");
	if (!shell_lvl)
	{
		minishell->shell_level = 1;
		return ;
	}
	shell_lvl_num = ft_atoi(shell_lvl);
	minishell->shell_level = shell_lvl_num + 1;
	shell_lvl = ft_itoa(minishell->shell_level);
	if (!shell_lvl)
		memory_allocation_failed_error_exit();
	if (!env_variables_set(&minishell->env_variables_manager, "SHLVL",
			shell_lvl))
		memory_allocation_failed_error_exit();
	mem_free(shell_lvl);
}

bool	setup_minishell(t_minishell *minishell, char *env[])
{
	env_variables_add_from_env(&minishell->env_variables_manager, env);
	increment_shell_lvl(minishell);
	env_variables_set(&minishell->env_variables_manager, "?", "0");
	if (minishell->shell_level > 100)
	{
		display_error_message("Maximum shell recursion excedded!");
		env_variables_free(&minishell->env_variables_manager);
		return (false);
	}
	load_config_file(minishell, ".ghiblirc");
	load_history_file(minishell, ".ghiblistory");
	return (true);
}
