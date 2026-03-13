/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:03:48 by yben-dje          #+#    #+#             */
/*   Updated: 2025/10/22 15:44:21 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	big_index;
	size_t	little_index;
	size_t	max_size;

	big_index = 0;
	max_size = ft_strlen(big);
	if (!little[0])
		return ((char *)big);
	while (big[big_index] && big_index < len && big_index < max_size)
	{
		little_index = 0;
		while (little[little_index] && big_index + little_index < len
			&& big_index < max_size)
		{
			if (big[big_index + little_index] != little[little_index])
				break ;
			little_index++;
		}
		if (little[little_index] == 0 && big_index <= max_size)
			return ((char *)big + big_index);
		big_index++;
	}
	return (NULL);
}
