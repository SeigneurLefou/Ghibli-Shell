/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:24:06 by marvin            #+#    #+#             */
/*   Updated: 2025/10/24 16:59:24 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*sub_str;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
	{
		sub_str = ft_calloc(1, sizeof(char));
		return (sub_str);
	}
	size = ft_strlen(s + start);
	if (len < size)
		size = len;
	sub_str = ft_calloc(size + 1, sizeof(char));
	if (!sub_str)
		return (NULL);
	ft_memcpy(sub_str, s + start, size);
	sub_str[size] = 0;
	return (sub_str);
}
