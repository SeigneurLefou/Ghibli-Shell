/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/23 14:59:54 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	write(1, "^C\n", 3);
	(void)sig;
	return ;
}

char	*handle_prompt(t_minishell *minishell)
{
	char	*line;
	char	*res;
	char	*prompt_line;

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
		{
			printf("exit\n");
			rl_clear_history();
			exit(0);
		}
		if (line && *line)
		{
			add_history(line);
			main_token(line, minishell);
		}
		if (!ft_strcmp(line, "exit"))
		{
			printf("exit\n");
			rl_clear_history();
			exit(0);
		}
		res = line;
		free(line);
	}
	rl_clear_history();
	return (res);
}
