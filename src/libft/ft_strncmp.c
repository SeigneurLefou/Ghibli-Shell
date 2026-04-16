/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:04:04 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/16 21:16:53 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n && s1[index] && s2[index] && s1[index] == s2[index])
		index++;
	if (index < n)
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	return (0);
}
