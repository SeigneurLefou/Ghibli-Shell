/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:59:14 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/29 18:24:38 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "exits.h"

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
	array = mem_alloc(to_alloc, default_error_exit, NULL, 0b1);
	if (!array)
		return (NULL);
	ft_bzero(array, to_alloc);
	return (array);
}
