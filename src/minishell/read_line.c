/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/05/12 15:31:10 by yben-dje         ###   ########.fr       */
=======
/*   Updated: 2026/05/05 20:59:25 by yben-dje         ###   ########.fr       */
>>>>>>> 345ebe4 ([Ponyo/Arrietty] Add support for $? and even better prompt line)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_signal = 0;

static void	trimmed_line_exec(char *line, char *trimmed,
				t_minishell *minishell, bool *first_sigint)
{
	if (line && trimmed && trimmed[0])
	{
		*first_sigint = true;
		add_history(trimmed);
		add_to_history_file(minishell, ".ghiblistory", trimmed);
		main_token(trimmed, minishell);
	}
}

void	handle_prompt(t_minishell *minishell)
{
	char	*line;
	char	*prompt_line;
	char	*trimmed;
	bool	first_sigint;
	int		stdin_save;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	stdin_save = dup(0);
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
		if (ft_strlen(line) > 32768)
		{
			display_error_message("The input line is too long. Max is 32768.");
			free(line);
			continue ;
		}
		if (!line)
		{
			if (g_signal > 0)
			{
				g_signal = -1;
				dup2(stdin_save, 0);
				rl_replace_line("", 1);
<<<<<<< HEAD
				env_variables_set(&minishell->env_variables_manager, "?",
					"130");
=======
				env_variable_manager_set(&minishell->env_variables_manager, "?",
						"130");
>>>>>>> 345ebe4 ([Ponyo/Arrietty] Add support for $? and even better prompt line)
				if (first_sigint)
					write(1, "\n", 1);
				rl_on_new_line();
				first_sigint = false;
				continue ;
			}
			else
				minishell->request_exit = true;
		}
		else
			trimmed = ft_strtrim(line, "\r\n \t");
		if (line)
			trimmed_line_exec(line, trimmed, minishell, &first_sigint);
		if (minishell->request_exit)
			break ;
	}
	close(stdin_save);
	rl_clear_history();
}
