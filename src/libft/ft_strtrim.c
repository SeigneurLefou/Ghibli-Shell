/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:24:04 by marvin            #+#    #+#             */
/*   Updated: 2026/06/03 14:31:59 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_calloc2(size_t nmemb, size_t size)
{
	size_t	to_alloc;
	void	*array;

	if (!nmemb || !size)
	{
		array = NULL;
		return (array);
	}
	to_alloc = nmemb * size;
	if (nmemb != to_alloc / size)
		return (NULL);
	array = mem_alloc(to_alloc, NULL, NULL, 0b1);
	if (!array)
		return (NULL);
	ft_bzero(array, to_alloc);
	return (array);
}

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

static char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*sub_str;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
	{
		sub_str = ft_calloc2(1, sizeof(char));
		return (sub_str);
	}
	size = ft_strlen(s + start);
	if (len < size)
		size = len;
	sub_str = ft_calloc2(size + 1, sizeof(char));
	if (!sub_str)
		return (NULL);
	ft_memcpy(sub_str, s + start, size);
	sub_str[size] = 0;
	return (sub_str);
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
		new = ft_calloc2(1, sizeof(char));
		return (new);
	}
	start = 0;
	while (s1[start] && contains(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end && contains(set, s1[end]))
		end--;
	new = ft_substr2(s1, start, end - start + 1);
	return (new);
}
