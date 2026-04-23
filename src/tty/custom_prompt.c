/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:54:55 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/23 14:29:21 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tty.h"

static bool	is_flag_active(char flag, t_minishell *minishell)
{
	char	*home;
	char	*pwd;

	home = env_variable_manager_get_single(&minishell->env_variables_manager,
			"HOME");
	pwd = env_variable_manager_get_single(&minishell->env_variables_manager,
			"PWD");
	if (flag == 'h')
		return (pwd && home && !ft_strncmp(home, pwd, ft_strlen(home)));
	// TODO : TEMP
	return (false);
}

static char	parse_escape(char escaped_char)
{
	if (escaped_char == 'n')
		return ('\n');
	if (escaped_char == 't')
		return ('\t');
	if (escaped_char == 'v')
		return ('\v');
	if (escaped_char == 'e')
		return ('\e');
	if (escaped_char == 'a')
		return ('\a');
	else
		return (escaped_char);
}

static bool	push_expand(t_vec *rendered, char *expand)
{
	unsigned int	index;

	if (!expand)
		return (true);
	index = 0;
	while (expand[index])
	{
		if (!vec_append(rendered, &expand[index]))
			return (false);
		index++;
	}
	return (true);
}

static bool	expand_prompt_custom(t_vec *rendered, char c,
		t_minishell *minishell)
{
	char	*str;

    str = NULL;
	if (c == 'l')
		str = env_variable_manager_get_single(&minishell->env_variables_manager,
				"PWD");
    if (c == 'u')
		str = env_variable_manager_get_single(&minishell->env_variables_manager,
				"USER");
    push_expand(rendered, str);
    return (true);
}

char	*render_prompt(char *base_prompt, t_minishell *minishell)
{
	unsigned int	index;
	t_vec			rendered;
	char			flag;
	char			*prompt;
	bool			flag_result;
	char			c;

	index = 0;
	if (!base_prompt || !vec_init(&rendered, sizeof(char), 16))
		return (NULL);
	while (base_prompt[index])
	{
		if ((base_prompt[index] == '%' || base_prompt[index] == '!')
			&& base_prompt[index + 1] && base_prompt[index + 2])
		{
			flag = base_prompt[index + 1];
			index += 2;
			flag_result = is_flag_active(flag, minishell);
			if ((base_prompt[index - 2] == '%' && flag_result)
				|| (base_prompt[index - 2] == '!' && !flag_result))
			{
				while (base_prompt[index] && base_prompt[index] != ';')
				{
					if (base_prompt[index + 1] && base_prompt[index] == '\\')
						c = parse_escape(base_prompt[++index]);
                    else if (base_prompt[index] == '@' && base_prompt[index + 1])
                    {
                        index++;
                        expand_prompt_custom(&rendered, base_prompt[index], minishell);
                        index++;
                        continue;
                    }
					else
						c = base_prompt[index];
					if (!vec_append(&rendered, &c))
					{
						vec_free(&rendered);
						return (NULL);
					}
					if (base_prompt[index])
						index++;
				}
			}
			else
			{
				while (base_prompt[index] && base_prompt[index] != ';')
					index++;
			}
		}
		else if (base_prompt[index] == '\\' && (base_prompt[index + 1] == '%'
				|| base_prompt[index + 1] == '!' || base_prompt[index
				+ 1] == '@'))
		{
			if (!vec_append(&rendered, &base_prompt[++index]))
			{
				vec_free(&rendered);
				return (NULL);
			}
		}
		else if (base_prompt[index] == '@' && base_prompt[index + 1])
		{
			index++;
            expand_prompt_custom(&rendered, base_prompt[index], minishell);
		}
		else
		{
			if (base_prompt[index + 1] && base_prompt[index] == '\\')
				c = parse_escape(base_prompt[++index]);
			else
				c = base_prompt[index];
			if (!vec_append(&rendered, &c))
			{
				vec_free(&rendered);
				return (NULL);
			}
		}
		if (!base_prompt[index])
			break ;
		index++;
	}
	prompt = vec_to_cstring(&rendered);
	vec_free(&rendered);
	return (prompt);
}
