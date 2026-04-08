/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:09:36 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/02 19:16:34 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


void	safe_free(char **pointer)
{
	if (*pointer)
		free(*pointer);
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
	new = malloc(dst_len + line_size + 1);
	if (!new)
		return (NULL);
	dst_len = 0;
	while (dst && dst[dst_len])
	{
		new[dst_len] = dst[dst_len];
		dst_len++;
	}
	if (dst)
		free(dst);
	src_len = 0;
	while (src[src_len] && src_len < line_size)
		new[dst_len++] = src[src_len++];
	new[dst_len] = '\0';
	return (new);
}