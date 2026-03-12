/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:25:11 by yben-dje          #+#    #+#             */
/*   Updated: 2026/01/15 13:06:26 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	int		size;

	size = ft_strlen(s) + 1;
	new = malloc(size);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, size);
	return (new);
}
