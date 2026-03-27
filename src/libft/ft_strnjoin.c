/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:38:30 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/27 14:56:57 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*ft_alloc_char(char *s1, char *s2, size_t size)
{
	size_t	len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	len = 0;
	len += ft_strlen(s1);
	len += ft_strlen(s2);
	if (len > size)
		len = size;
	res = ft_calloc(len + 1, sizeof(char));
	return (res);
}

char	*ft_strnjoin(char *s1, char *s2, size_t size)
{
	char	*joinstr;
	size_t	i;
	size_t	j;

	joinstr = ft_alloc_char(s1, s2, size);
	if (!joinstr)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		joinstr[i] = s1[i];
		i++;
	}
	if (s1)
		free(s1);
	j = 0;
	while (s2 && s2[j])
	{
		joinstr[i] = s2[j];
		i++;
		j++;
	}
	return (joinstr);
}
