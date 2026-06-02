/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:03:00 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/02 11:11:09 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_manager.h"

unsigned int	get_char_pos(t_vec *expr, unsigned int index)
{
	unsigned int	char_index;
	t_token			*token;

	char_index = 0;
	while (index--)
	{
		token = vec_get(expr, index);
		char_index += token->data.size + 1;
	}
	return (char_index);
}

unsigned int	underline_error(t_vec *expr, unsigned int token_index,
		unsigned int current_index, char c)
{
	unsigned int	char_index;
	unsigned int	index;
	t_token			*token;

	char_index = get_char_pos(expr, token_index) - current_index;
	index = char_index;
	while (index--)
		write(2, " ", 1);
	token = vec_get(expr, token_index);
	index = token->data.size;
	write(2, "\x1b[33m", 6);
	while (index--)
		write(2, &c, 1);
	write(2, "\x1b[0m", 5);
	return (char_index + token->data.size);
}

void	display_error_message(char *msg)
{
	write(2, "\x1b[31mGhibliShell error: ", 25);
	write(2, msg, ft_strlen(msg));
	write(2, "\x1b[0m\n", 6);
}

void	show_error(t_vec *expr, char *msg, int index1, int index2)
{
	unsigned int	index;
	unsigned int	offset;
	t_token			*token;

	display_error_message(msg);
	if (index1 >= (int)expr->size)
		index1 = expr->size - 1;
	if (index2 >= (int)expr->size)
		index2 = expr->size - 1;
	index = 0;
	offset = 0;
	while (index < expr->size)
	{
		token = vec_get(expr, index);
		write(2, token->data.data, token->data.size);
		index++;
		write(2, " ", 1);
	}
	write(2, "\n", 1);
	if (index1 <= index2)
	{
		if (index1 >= 0)
			offset = underline_error(expr, index1, 0, '^');
		if (index2 >= 0 && index1 != index2)
			underline_error(expr, index2, offset, '~');
	}
	else
	{
		if (index2 >= 0)
			offset = underline_error(expr, index2, 0, '~');
		if (index1 >= 0)
			underline_error(expr, index1, offset, '^');
	}
	write(2, "\n", 1);
}
