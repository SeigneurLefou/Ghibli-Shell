/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:03:12 by yben-dje          #+#    #+#             */
/*   Updated: 2025/10/23 18:04:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		src_index;
	size_t	dst_index;
	size_t	initial_dest_size;
	size_t	src_size;

	src_size = ft_strlen(src);
	if (!size)
		return (src_size);
	initial_dest_size = ft_strlen(dst);
	dst_index = initial_dest_size;
	src_index = 0;
	if (dst_index >= size)
		return (size + src_size);
	while (dst_index < size - 1 && dst_index < initial_dest_size + src_size)
	{
		dst[dst_index] = src[src_index];
		src_index++;
		dst_index++;
	}
	dst[dst_index] = 0;
	return (initial_dest_size + src_size);
}
