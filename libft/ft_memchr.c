/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:11:19 by yben-dje          #+#    #+#             */
/*   Updated: 2025/10/27 18:38:04 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*pointer;

	if (!n)
		return (NULL);
	pointer = (char *)s;
	while (--n && *pointer != (char)c)
		pointer++;
	if (*pointer != (char)c)
		return (NULL);
	return (pointer);
}
