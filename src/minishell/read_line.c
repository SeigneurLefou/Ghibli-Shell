/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/24 16:05:10 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_prompt(t_minishell *minishell)
{
	char	*line;
	char	*prompt_line;
	char *trimmed;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	while (1)
	{
		prompt_line = get_prompt_line(minishell);
		if (prompt_line)
			printf("%s", prompt_line);
		line = readline("");
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
