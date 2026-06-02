/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:10:19 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/01 15:11:28 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "exits.h"

void	safe_free(char **pointer)
{
	if (*pointer)
		mem_free(*pointer);
	*pointer = NULL;
}

int	contains(char *str, char c)
{
	if (!str)
		return (0);
	while (*str)
		if (*(str++) == c)
			return (1);
	return (0);
}

char	*gnl_strjoin(char *dst, const char *src, size_t line_size)
{
	size_t	dst_len;
	size_t	src_len;
	char	*new;

	dst_len = 0;
	while (dst && dst[dst_len])
		dst_len++;
	new = mem_alloc(dst_len + line_size + 1, default_error_exit, NULL, 0b1);
	if (!new)
		return (NULL);
	dst_len = 0;
	while (dst && dst[dst_len])
	{
		new[dst_len] = dst[dst_len];
		dst_len++;
	}
	if (dst)
		mem_free(dst);
	src_len = 0;
	while (src[src_len] && src_len < line_size)
		new[dst_len++] = src[src_len++];
	new[dst_len] = '\0';
	return (new);
}
