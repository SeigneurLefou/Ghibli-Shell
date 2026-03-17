/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:18:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/02/19 13:31:03 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*ft_alloc_char(char *s1, char *s2)
{
	size_t	len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	len = 0;
	if (s1)
		len += ft_strlen(s1);
	if (s2)
		len += ft_strlen(s2);
	res = ft_calloc(len + 1, sizeof(char));
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joinstr;
	size_t	i;
	size_t	j;

	joinstr = ft_alloc_char(s1, s2);
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
