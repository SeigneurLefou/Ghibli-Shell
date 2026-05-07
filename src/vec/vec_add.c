/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:16:20 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/07 13:40:16 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

bool	vec_append(t_vec *vec, void *data)
{
	char	*new_data;

	assert((int[]){vec != NULL, data != NULL, 42}, "Null passed to vec_append.");
	if (!vec->data || vec->size >= vec->allocated_size)
	{
		new_data = malloc((vec->allocated_size + vec->buffering_size)
				* vec->type_size);
		if (!new_data)
			return (false);
		if (vec->data)
			ft_memcpy(new_data, vec->data, vec->allocated_size * vec->type_size);
		vec->allocated_size += vec->buffering_size;
		free(vec->data);
		vec->data = new_data;
	}
	ft_memcpy(vec->data + vec->size * vec->type_size, data, vec->type_size);
	vec->size++;
	return (true);
}

bool	vec_expand_and_free(t_vec *vec, t_vec *other)
{
	char			*new_data;
	unsigned int	alloc_size;

	assert((int[]){vec != NULL, other != NULL, 42}, "Null passed to vec_expand_and_free.");
	assert((int[]){vec->type_size == other->type_size, 42}, "Typesize is different between vec and other.");
	alloc_size = (vec->size + other->size + vec->buffering_size)
		* vec->type_size;
	new_data = malloc(alloc_size);
	if (!new_data)
		return (false);
	if (vec->data)
		ft_memcpy(new_data, vec->data, vec->size * vec->type_size);
	vec->allocated_size = vec->size + other->size + vec->buffering_size;
	if (other->data)
		ft_memcpy(new_data + vec->size * vec->type_size, other->data, other->size
			* other->type_size);
	vec->size += other->size;
	vec->data = new_data;
	vec_free(other);
	return (true);
}

bool	vec_expand(t_vec *vec, t_vec *other)
{
	char			*new_data;
	unsigned int	alloc_size;

	assert((int[]){vec != NULL, other != NULL, 42}, "Null passed to vec_expand_and_free.");
	assert((int[]){vec->type_size == other->type_size, 42}, "Typesize is different between vec and other.");
	alloc_size = (vec->size + other->size + vec->buffering_size)
		* vec->type_size;
	new_data = malloc(alloc_size);
	if (!new_data)
		return (false);
	if (vec->data)
		ft_memcpy(new_data, vec->data, vec->size * vec->type_size);
	vec->allocated_size = vec->size + other->size + vec->buffering_size;
	if (other->data)
		ft_memcpy(new_data + vec->size * vec->type_size, other->data, other->size
			* other->type_size);
	vec->size += other->size;
	vec->data = new_data;
	return (true);
}
