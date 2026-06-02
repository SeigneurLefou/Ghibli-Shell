/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:08:39 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/01 14:08:40 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

void	echo_print_format(char **parts, int fds[2])
{
	unsigned int	index;
	unsigned int	index2;
	char			c;

	index = 1;
	while (parts[index])
	{
		index2 = 0;
		while (parts[index][index2])
		{
			if (parts[index][index2 + 1] && parts[index][index2] == '\\')
				c = parse_escape(parts[index][++index2]);
			else
				c = parts[index][index2];
			write(fds[1], &c, 1);
			index2++;
		}
		index++;
		if (parts[index])
			write(fds[1], " ", 1);
	}
}

void	echo_print(char **parts, int fds[2])
{
	unsigned int	index;
	unsigned int	index2;
	char			c;

	index = 1;
	while (parts[index])
	{
		index2 = 0;
		while (parts[index][index2])
		{
			c = parts[index][index2];
			write(fds[1], &c, 1);
			index2++;
		}
		index++;
		if (parts[index])
			write(fds[1], " ", 1);
	}
}

int	parse_args(int argc, char **argv, bool *newline, bool *escapes)
{
	int		index;
	int		index2;
	bool	temp_flags[2];

	temp_flags[0] = *newline;
	temp_flags[1] = *escapes;
	index = 1;
	while (index < argc && argv[index][0] == '-' && argv[index][1])
	{
		index2 = 1;
		while (argv[index][index2])
		{
			if (argv[index][index2] == 'n')
				temp_flags[0] = false;
			else if (argv[index][index2] == 'e')
				temp_flags[1] = true;
			else
				return (index - 1);
			index2++;
		}
		*newline = temp_flags[0];
		*escapes = temp_flags[1];
		index++;
	}
	return (index - 1);
}

int	builtin_echo(int argc, char **argv, int fds[2])
{
	bool	newline;
	bool	escapes;
	int		argc_offset;

	newline = true;
	escapes = false;
	argc_offset = parse_args(argc, argv, &newline, &escapes);
	if (escapes)
		echo_print_format(argv + argc_offset, fds);
	else
		echo_print(argv + argc_offset, fds);
	if (newline)
		write(fds[1], "\n", 1);
	return (0);
}
