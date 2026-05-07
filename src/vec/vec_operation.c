/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:16:31 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/07 13:31:18 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	*vec_get(t_vec *vec, unsigned int index)
{
	assert((int[]){vec != NULL, 42}, "Null passed to vec_get.");
	if (index >= vec->size)
		return (NULL);
	return (vec->data + index * vec->type_size);
}

void	vec_set(t_vec *vec, unsigned int index, void *data)
{
	assert((int[]){vec != NULL, 42}, "Null passed to vec_get.");
	assert((int[]){index >= vec->size, 42}, "Index is out of bounds.");
	ft_memcpy(vec->data + index * vec->type_size, data, vec->type_size);
}
