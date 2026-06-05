/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:55:25 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 20:00:42 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tty.h"

char	parse_escape(char escaped_char)
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

bool	can_escape(char *base_prompt, unsigned int index)
{
	return (base_prompt[index] == '\\' && (base_prompt[index + 1] == '%'
			|| base_prompt[index + 1] == '!' || base_prompt[index + 1] == '@'
			|| base_prompt[index + 1] == '\\'));
}
