/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:03:57 by yben-dje          #+#    #+#             */
/*   Updated: 2025/10/22 10:20:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*pointer;
	char	*last;
	size_t	len;

	last = 0;
	pointer = (char *)s;
	len = ft_strlen(pointer);
	if (!(char)c)
		return (pointer + len);
	while (*pointer)
	{
		if (*pointer == (char)c)
			last = pointer;
		pointer++;
	}
	return (last);
}
