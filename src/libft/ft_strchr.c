/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:02:54 by yben-dje          #+#    #+#             */
/*   Updated: 2025/10/22 10:20:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*pointer;
	size_t	len;

	pointer = (char *)s;
	len = ft_strlen(pointer);
	if (!(char)c)
		return (pointer + len);
	while (*pointer != 0 && *pointer != (char)c)
		pointer++;
	if (*pointer == 0)
		return (0);
	return (pointer);
}
