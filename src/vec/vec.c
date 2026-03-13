/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:03:57 by yben-dje          #+#    #+#             */
/*   Updated: 2026/03/11 14:59:19 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

bool	vec_init(t_vec *vec, size_t type_size, unsigned int buffering_size)
{
	vec->buffering_size = buffering_size;
	vec->size = 0;
	vec->type_size = type_size;
	vec->data = malloc(buffering_size * vec->type_size);
	vec->allocated_size = buffering_size;
	if (!vec->data)
		return (false);
	return (true);
}

void	*vec_get(t_vec *vec, unsigned int index)
{
	if (index >= vec->size)
		return (NULL);
	return (vec->data + index * vec->type_size);
}

bool	vec_append(t_vec *vec, void *data)
{
	char	*new_data;

	if (vec->size >= vec->allocated_size)
	{
		new_data = malloc((vec->allocated_size + vec->buffering_size)
				* vec->type_size);
		if (!new_data)
			return (false);
		ft_memcpy(new_data, vec->data, vec->allocated_size * vec->type_size);
		vec->allocated_size += vec->buffering_size;
		free(vec->data);
		vec->data = new_data;
	}
	ft_memcpy(vec->data + vec->size * vec->type_size, data, vec->type_size);
	vec->size++;
	return (true);
}

bool	vec_truncate(t_vec *vec)
{
	char	*new_data;

	new_data = malloc(vec->size * vec->type_size);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, vec->data, vec->size * vec->type_size);
	vec->allocated_size = vec->size;
	free(vec->data);
	vec->data = new_data;
	return (true);
}

void	vec_free(t_vec *vec)
{
	free(vec->data);
}
