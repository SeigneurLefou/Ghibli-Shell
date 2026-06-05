/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/05 18:41:36 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	trimmed_line_exec(char *line, char *trimmed, t_minishell *minishell,
		bool *first_sigint)
{
	if (!trimmed)
	{
		free(line);
		default_error_exit(NULL);
	}
	if (trimmed[0])
	{
		*first_sigint = true;
		add_history(trimmed);
		add_to_history_file(minishell, ".ghiblistory", trimmed);
		disable_sig_handler();
		main_token(trimmed, minishell);
		setup_sig_handler();
	}
}

bool	handle_null_line(t_minishell *minishell, bool *first_sigint)
{
	if (g_signal > 0)
	{
		g_signal = -1;
		dup2(minishell->stdin_save, 0);
		rl_replace_line("", 1);
		env_variables_set(&minishell->env_variables_manager, "?", "130");
		minishell->last_status = 130;
		if (*first_sigint)
			write(1, "\n", 1);
		rl_on_new_line();
		*first_sigint = false;
		return (false);
	}
	else
	{
		minishell->request_exit = true;
		write(2, "exit\n", 6);
	}
	return (true);
}

bool	read_prompt_line(char **line, t_minishell *minishell)
{
	char	*prompt_line;

	setup_sig_handler();
	if (g_signal == SIGQUIT)
	{
		env_variables_set(&minishell->env_variables_manager, "?", "131");
		minishell->last_status = 131;
		g_signal = -1;
	}
	prompt_line = get_prompt_line(minishell);
	*line = NULL;
	if (prompt_line)
	{
		*line = readline(prompt_line);
		mem_free(prompt_line);
	}
	else
		*line = readline("$> ");
	if (ft_strlen(*line) > 32768)
	{
		display_error_message("The input line is too long. Max is 32768.");
		free(*line);
		return (false);
	}
	return (true);
}

void	handle_prompt(t_minishell *minishell)
{
	char	*line;
	char	*trimmed;
	bool	first_sigint;

	minishell->stdin_save = dup(0);
	first_sigint = true;
	while (1)
	{
		if (!read_prompt_line(&line, minishell))
			continue ;
		if (!line)
		{
			if (!handle_null_line(minishell, &first_sigint))
				continue ;
		}
		else
		{
			trimmed = ft_strtrim(line, "\r\n \t\v\f");
			trimmed_line_exec(line, trimmed, minishell, &first_sigint);
		}
		if (minishell->request_exit)
			break ;
	}
	close(minishell->stdin_save);
	rl_clear_history();
}
