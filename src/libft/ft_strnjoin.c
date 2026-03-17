/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:38:30 by lchamard          #+#    #+#             */
/*   Updated: 2026/02/18 08:49:44 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnjoin(char *s1, char *s2, size_t size)
{
	char	*joinstr;
	size_t	i;
	size_t	j;

	joinstr = ft_calloc(size + 1, sizeof(char));
	if (!joinstr)
		return (NULL);
	i = 0;
	while (s1 && s1[i] && i < size)
	{
		joinstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && i < size)
	{
		joinstr[i] = s2[j];
		i++;
		j++;
	}
	return (joinstr);
}
