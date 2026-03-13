/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:11:23 by yben-dje          #+#    #+#             */
/*   Updated: 2025/10/21 17:02:56 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (!n)
		return (0);
	while (((char *)s1)[index] == ((char *)s2)[index] && index < n - 1)
		index++;
	return (((unsigned char *)s1)[index] - ((unsigned char *)s2)[index]);
}
