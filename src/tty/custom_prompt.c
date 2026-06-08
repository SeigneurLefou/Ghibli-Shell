/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:54:55 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 20:05:53 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tty.h"

void	add_regular_char_and_escape(char *base_prompt, unsigned int *index,
		t_vec *rendered)
{
	char	c;

	if (base_prompt[(*index) + 1] && base_prompt[(*index)] == '\\')
		c = parse_escape(base_prompt[++(*index)]);
	else
		c = base_prompt[(*index)];
	vec_append(rendered, &c);
}

char	*render_prompt(char *base_prompt, t_minishell *minishell)
{
	unsigned int	index;
	t_vec			rendered;
	char			*prompt;

	index = 0;
	vec_init(&rendered, sizeof(char), 16);
	while (base_prompt[index])
	{
		if ((base_prompt[index] == '%' || base_prompt[index] == '!')
			&& base_prompt[index + 1] && base_prompt[index + 2])
			process_condicionals(base_prompt, minishell, &index, &rendered);
		else if (can_escape(base_prompt, index))
			vec_append(&rendered, &base_prompt[++index]);
		else if (base_prompt[index] == '@' && base_prompt[index + 1])
			expand_prompt_custom(&rendered, base_prompt[++index], minishell);
		else
			add_regular_char_and_escape(base_prompt, &index, &rendered);
		if (!base_prompt[index])
			break ;
		index++;
	}
	prompt = vec_to_cstring(&rendered);
	vec_free(&rendered);
	return (prompt);
}

char	*get_prompt_line(t_minishell *minishell)
{
	char	*prompt_line;

	prompt_line = env_variables_get(&minishell->env_variables_manager,
			"PROMPT");
	if (prompt_line)
		prompt_line = render_prompt(prompt_line, minishell);
	return (prompt_line);
}
