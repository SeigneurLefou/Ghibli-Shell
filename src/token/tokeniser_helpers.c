/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:37:46 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 13:50:24 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	get_escape(char escaped_char)
{
	if (escaped_char == '\\')
		return ('\\');
	if (escaped_char == '"')
		return ('"');
	if (escaped_char == '\'')
		return ('\'');
	if (escaped_char == ' ')
		return (' ');
	else
		return (0);
}

char	is_escape(char escaped_char, char quote)
{
	if (quote == '"')
		return (escaped_char == '\\' || escaped_char == '"');
	else
		return (false);
}

bool	is_valid_expand_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	is_tilde_escape_compatible(char c)
{
	return (ft_isspace(c) || c == '/' || c == '\0' || c == '|' || c == '&'
		|| c == '<' || c == '>');
}
