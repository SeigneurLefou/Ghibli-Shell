/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/01 15:26:58 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal = 0;

void handle_prompt(t_minishell *minishell)
{
	char	*line;
	char	*prompt_line;
	char *trimmed;
	bool	first_sigint;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	int stdin_save = dup(0);
	first_sigint = true;
	while (1)
	{
		prompt_line = get_prompt_line(minishell);
		line = NULL;
		if (prompt_line)
		{
			line = readline(prompt_line);
			free(prompt_line);
		}
		else
			line = readline("$>");
		if (!line)
		{
			if (g_signal > 0)
			{
				g_signal = -1;
				dup2(stdin_save, 0);
				rl_replace_line("", 1);
				if (first_sigint)
					write(1, "\n", 1);
				rl_on_new_line();
				first_sigint = false;
				continue;
			}
			else
				minishell->request_exit = true;
		}
		else
			trimmed = ft_strtrim(line, "\r\n \t");
		if (line && trimmed)
		{
			if (trimmed[0])
			{
				first_sigint = true;
				add_history(trimmed);
				add_to_history_file(minishell, ".ghiblistory", trimmed);
				main_token(trimmed, minishell);
				free(trimmed);
			}
		}
		free(line);
		if (minishell->request_exit)
			break;
	}
	close(stdin_save);
	rl_clear_history();
}
