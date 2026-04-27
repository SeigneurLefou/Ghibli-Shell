/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/24 13:25:39 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	write(1, "^C\n", 3);
	(void)sig;
	return ;
}

void handle_prompt(t_minishell *minishell)
{
	char	*line;
	char	*prompt_line;
	char *trimmed;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	while (1)
	{
		prompt_line = env_variable_manager_get_single(&minishell->env_variables_manager, "PROMPT");
		if (prompt_line)
		{
			prompt_line = render_prompt(prompt_line, minishell);
			if (!prompt_line)
				prompt_line = "$> ";
		}
		else
			prompt_line = "$> ";
		line = readline(prompt_line);
		if (!line)
			minishell->request_exit = true;
		else
			trimmed = ft_strtrim(line, "\r\n \t");
		if (line && trimmed)
		{
			if (trimmed[0])
			{
				add_history(trimmed);
				main_token(trimmed, minishell);
				free(trimmed);
			}
		}
		free(line);
		if (minishell->request_exit)
			break;
	}
	rl_clear_history();
}
