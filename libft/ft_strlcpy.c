/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:01:24 by yben-dje          #+#    #+#             */
/*   Updated: 2025/10/22 15:42:19 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	src_size;

	index = 0;
	src_size = ft_strlen(src);
	if (index >= size)
		return (size + src_size);
	while (index < size - 1 && index < src_size)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = 0;
	return (src_size);
}
