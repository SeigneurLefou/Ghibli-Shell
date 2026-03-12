/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:23:52 by marvin            #+#    #+#             */
/*   Updated: 2025/10/22 15:47:48 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_reversed(char *buf, int size)
{
	char	*new;
	int		index;

	index = 0;
	new = ft_calloc(size + 1, 1);
	if (!new)
		return (NULL);
	while (size--)
		new[index++] = buf[size];
	return (new);
}

char	*ft_itoa(int n)
{
	char		buf[11];
	int			index;
	long int	temp_n;
	char		*new;

	temp_n = n;
	index = 0;
	if (n < 0)
		temp_n = -temp_n;
	if (n == 0)
	{
		new = ft_strdup("0");
		return (new);
	}
	while (temp_n)
	{
		buf[index] = '0' + temp_n % 10;
		index++;
		temp_n /= 10;
	}
	if (n < 0)
		buf[index++] = '-';
	new = get_reversed(buf, index);
	return (new);
}
