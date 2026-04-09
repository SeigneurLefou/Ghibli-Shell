/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:36:36 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/09 11:36:26 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	write(1, "^C\n", 3);
	rl_new
	return ;
}

char	*str_append_char(char *str, char c)
{
	size_t	i;
	char	*new_str;

	i = 0;
	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	return (new_str);
}

char	*expand_variable(char *raw_line, char *prompt_line, size_t *i)
{
	char	*var_name;
	char	*var_content;
	size_t	k;

	(*i)++;
	k = 0;
	var_name = NULL;
	while (raw_line[*i] && ft_isalnum(raw_line[*i]))
	{
		var_name = str_append_char(var_name, raw_line[*i]);
		(*i)++;
	}
	var_content = getenv(var_name);
	free(var_name);
	while (var_content && var_content[k])
	{
		prompt_line = str_append_char(prompt_line, var_content[k]);
		k++;
	}
	return (prompt_line);
}

char	*expand_prompt_line(char *raw_line)
{
	char	*prompt_line;
	size_t	i;

	prompt_line = NULL;
	i = 0;
	while (raw_line && raw_line[i] && raw_line[i] != '\"')
	{
		if (raw_line[i] == '$')
			prompt_line = expand_variable(raw_line, prompt_line, &i);
		else
		{
			prompt_line = str_append_char(prompt_line, raw_line[i]);
			i++;
		}
	}
	return (prompt_line);
}

char	*set_prompt_line(void)
{
	char	*prompt;
	char	*line;
	int		fd;
	char	*path;

	path = ft_strdup(getenv("HOME"));
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
	prompt = expand_prompt_line(&line[17]);
	free(line);
	free(path);
	close(fd);
	return (prompt);
}

char	*handle_prompt(char *env[])
{
	char	*line;
	char	*res;
	char	*prompt_line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	while (1)
	{
		prompt_line = set_prompt_line();
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
			main_token(line, env);
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
