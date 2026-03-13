/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:23:59 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 17:55:05 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_sub_strings(const char *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			return (count);
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static size_t	word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static int	check_and_unwrap(char **strings_array, int index)
{
	if (!strings_array[index])
	{
		while (index--)
			free(strings_array[index]);
		free(strings_array);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**strings_array;
	int		len;
	int		index;

	index = count_sub_strings(s, c);
	strings_array = ft_calloc(index + 1, sizeof(char *));
	index = 0;
	if (!strings_array)
		return (NULL);
	while (s && *s)
	{
		len = word_len(s, c);
		if (len)
		{
			strings_array[index] = ft_substr(s, 0, len);
			if (check_and_unwrap(strings_array, index++))
				return (NULL);
			s += len;
			while (*s && *s == c)
				s++;
		}
		else
			s++;
	}
	return (strings_array);
}
