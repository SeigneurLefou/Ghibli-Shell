/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:16:31 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/04 17:16:32 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	*vec_get(t_vec *vec, unsigned int index)
{
	assert((int[]){vec != NULL, 42}, "Null passed to vec_get.");
	assert((int[]){vec->data != NULL, 42}, "Non-initialised vec.");
	if (index >= vec->size)
		return (NULL);
	return (vec->data + index * vec->type_size);
}

void	vec_set(t_vec *vec, unsigned int index, void *data)
{
	assert((int[]){vec != NULL, 42}, "Null passed to vec_get.");
	assert((int[]){vec->data != NULL, 42}, "Non-initialised vec.");
	assert((int[]){index >= vec->size, 42}, "Index is out of bounds.");
	ft_memcpy(vec->data + index * vec->type_size, data, vec->type_size);
}
