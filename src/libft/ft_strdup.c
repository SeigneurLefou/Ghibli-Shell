/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:25:11 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/29 18:20:29 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exits.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	int		size;

	size = ft_strlen(s) + 1;
	new = mem_alloc(size, default_error_exit, NULL, 0b1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s, size);
	return (new);
}
