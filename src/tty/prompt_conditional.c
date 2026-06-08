/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_conditional.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:57:37 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 20:07:18 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tty.h"

static bool	is_flag_active(char flag, t_minishell *minishell)
{
	char	*home;
	char	*pwd;

	if (flag == 'h')
	{
		home = env_variables_get(&minishell->env_variables_manager, "HOME");
		pwd = env_variables_get(&minishell->env_variables_manager, "PWD");
		return (pwd && home && !ft_strncmp(home, pwd, ft_strlen(home)));
	}
	if (flag == 's')
		return (!minishell->last_status);
	return (false);
}

static bool	parse_conditional(char *base_prompt, t_minishell *minishell,
		unsigned int *index, t_vec *rendered)
{
	char	c;

	if (base_prompt[(*index) + 1] && base_prompt[(*index)] == '\\')
	{
		if (base_prompt[(*index) + 1] == ';' || base_prompt[(*index) + 1] == '@'
			|| base_prompt[(*index) + 1] == '\\')
			c = base_prompt[++(*index)];
		else
			c = parse_escape(base_prompt[++(*index)]);
	}
	else if (base_prompt[(*index)] == '@' && base_prompt[(*index) + 1])
	{
		(*index)++;
		expand_prompt_custom(rendered, base_prompt[(*index)], minishell);
		(*index)++;
		return (false);
	}
	else
		c = base_prompt[(*index)];
	vec_append(rendered, &c);
	if (base_prompt[(*index)])
		(*index)++;
	return (true);
}

static void	walk_until_conditional_end(char *base_prompt, unsigned int *index)
{
	while (base_prompt[(*index)] && base_prompt[(*index)] != ';')
	{
		if (base_prompt[(*index)] == '\\' && (base_prompt[(*index) + 1] == ';'
				|| base_prompt[(*index) + 1] == '@' || base_prompt[(*index)
					+ 1] == '\\'))
			(*index)++;
		(*index)++;
	}
}

void	process_condicionals(char *base_prompt, t_minishell *minishell,
		unsigned int *index, t_vec *rendered)
{
	char	flag;
	bool	flag_result;

	flag = base_prompt[(*index) + 1];
	(*index) += 2;
	flag_result = is_flag_active(flag, minishell);
	if ((base_prompt[(*index) - 2] == '%' && flag_result)
		|| (base_prompt[(*index) - 2] == '!' && !flag_result))
	{
		while (base_prompt[(*index)] && base_prompt[(*index)] != ';')
		{
			if (!parse_conditional(base_prompt, minishell, index, rendered))
				continue ;
		}
	}
	else
		walk_until_conditional_end(base_prompt, index);
}
