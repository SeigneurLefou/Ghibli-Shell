/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:24:04 by marvin            #+#    #+#             */
/*   Updated: 2026/04/25 12:34:11 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contains(char const *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	if (!s1[0])
	{
		new = ft_calloc(1, sizeof(char));
		return (new);
	}
	start = 0;
	while (s1[start] && contains(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end && contains(set, s1[end]))
		end--;
	new = ft_substr(s1, start, end - start + 1);
	return (new);
}
