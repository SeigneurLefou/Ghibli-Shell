/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:56:24 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 20:06:21 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tty.h"

static void	push_expand(t_vec *rendered, char *expand)
{
	unsigned int	index;

	if (!expand)
		return ;
	index = 0;
	while (expand[index])
	{
		vec_append(rendered, &expand[index]);
		index++;
	}
	return ;
}

static char	*get_home_relative_pwd(t_minishell *minishell)
{
	char			*pwd;
	char			*home;
	unsigned int	home_size;

	pwd = env_variables_get(&minishell->env_variables_manager, "PWD");
	home = env_variables_get(&minishell->env_variables_manager, "HOME");
	if (!pwd || !home)
		return (NULL);
	home_size = ft_strlen(home);
	if (!ft_strncmp(home, pwd, home_size))
		return (pwd + home_size);
	return (pwd);
}

bool	expand_prompt_custom(t_vec *rendered, char c,
		t_minishell *minishell)
{
	char	*str;

	str = NULL;
	if (c == 'l')
		str = env_variables_get(&minishell->env_variables_manager, "PWD");
	if (c == 'u')
		str = env_variables_get(&minishell->env_variables_manager, "USER");
	if (c == 'r')
		str = get_home_relative_pwd(minishell);
	if (c == 's')
		str = env_variables_get(&minishell->env_variables_manager, "?");
	if (c == '1')
		str = "\001\x1b";
	if (c == '2')
		str = "\002";
	if (str)
		push_expand(rendered, str);
	return (true);
}
