/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/17 13:10:33 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	write(1, "^C\n", 3);
	(void)sig;
	return ;
}

char	*set_prompt_line(t_minishell *minishell)
{
	char	*prompt;
	char	*line;
	int		fd;
	char	*path;

	path = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
			"HOME"));
	path = ft_strjoin(path, "/.ghiblirc");
	fd = open(path, O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		free(path);
		return (NULL);
	}
	line = get_next_line(fd);
	while (line && ft_strncmp(line, "set prompt_line=\"", 17))
	{
		free(line);
		line = get_next_line(fd);
	}
	prompt = expand_line(minishell, &line[17]);
	free(line);
	free(path);
	if (fd > 2)
		close(fd);
	return (prompt);
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
		prompt_line = set_prompt_line(minishell);
		if (!prompt_line)
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
