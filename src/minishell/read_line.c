/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/19 11:43:19 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

/* Based on the examples given at https://circuitlabs.net/signal-handling-catching-signals-w-signal-sigaction */
bool	setup_sig_handler(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = handle_signal_default;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	if (sigaction(SIGTERM, &sa, NULL) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	return (true);
}

bool	disable_sig_handler(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	if (sigaction(SIGTERM, &sa, NULL) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	return (true);
}

static void	trimmed_line_exec(char *line, char *trimmed, t_minishell *minishell,
		bool *first_sigint)
{
	if (line && trimmed && trimmed[0])
	{
		*first_sigint = true;
		add_history(trimmed);
		add_to_history_file(minishell, ".ghiblistory", trimmed);
		disable_sig_handler();
		main_token(trimmed, minishell);
		setup_sig_handler();
	}
}

void	handle_prompt(t_minishell *minishell)
{
	char	*line;
	char	*prompt_line;
	char	*trimmed;
	bool	first_sigint;

	minishell->stdin_save = dup(0);
	first_sigint = true;
	while (1)
	{
		setup_sig_handler();
		prompt_line = get_prompt_line(minishell);
		line = NULL;
		if (prompt_line)
		{
			line = readline(prompt_line);
			free(prompt_line);
		}
		else
			line = readline("$> ");
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
				dup2(minishell->stdin_save, 0);
				rl_replace_line("", 1);
				env_variables_set(&minishell->env_variables_manager, "?",
					"130");
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
	close(minishell->stdin_save);
	rl_clear_history();
}
