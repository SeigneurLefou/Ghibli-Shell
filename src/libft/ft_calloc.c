/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:59:14 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/18 19:18:35 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
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
	array = mem_alloc(to_alloc, NULL, NULL);
	if (!array)
		return (NULL);
	ft_bzero(array, to_alloc);
	return (array);
}
