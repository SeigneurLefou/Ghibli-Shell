/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:24:03 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 17:51:58 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	new = ft_strdup(s);
	if (!new)
		return (NULL);
	while (f && new[index])
	{
		new[index] = f(index, new[index]);
		index++;
	}
	return (new);
}
