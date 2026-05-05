/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ghiblirc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:51:00 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/01 15:34:52 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ask_and_setup_ghiblirc(char *config_path)
{
	char	*choice;
	int		file;

	printf("%s", GHIBLIRC_SETUP_PROMPT);
	choice = readline("Your choice ([1]/2/3): ");
	if (choice && (choice[0] == '1' || choice[0] == '2' || choice[0] == '3'))
	{
		if (!choice[0] || choice[0] == '1' || choice[0] == '2')
		{
			file = open(config_path, O_WRONLY | O_CREAT, 0666);
			if (!file)
			{
				perror("GhibliShell");
				return ;
			}
			if (!choice[0] || choice[0] == '1')
				write(file, GHIBLIRC_DEFAULT, ft_strlen(GHIBLIRC_DEFAULT));
			write(1, "Your .ghiblirc file is now ready to use!\n", 42);
			close(file);
		}
	}
	else
		display_error_message("Invalid choice!");
	free(choice);
}

char	*get_config_file_path(t_minishell *minishell, char *config_file)
{
	char	*home_path;
	int		lenght;
	char	*complete_path;

	home_path = env_variable_manager_get_single(&minishell->env_variables_manager,
			"HOME");
	if (!home_path)
		return (NULL);
	lenght = ft_strlen(home_path);
	if (lenght < 2)
		return (NULL);
	if (home_path[lenght - 1] != '/')
		home_path = ft_strjoin(home_path, "/");
	if (!home_path)
		return (NULL);
	complete_path = ft_strjoin(home_path, config_file);
	free(home_path);
	return (complete_path);
}

void	load_config_file(t_minishell *minishell, char *config_file)
{
	char	*config_path;

	config_path = get_config_file_path(minishell, config_file);
	if (config_path)
	{
		if (!access(config_path, F_OK))
			execute_file(config_path, minishell);
		else
		{
			ask_and_setup_ghiblirc(config_path);
			execute_file(config_path, minishell);
		}
		free(config_path);
	}
}
