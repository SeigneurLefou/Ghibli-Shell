/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:04:45 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/07 13:29:43 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	vec_init(t_vec *vec, size_t type_size, unsigned int buffering_size)
{
	assert((int[]){vec != NULL, type_size >= 0, buffering_size >= 0, 42}, "Cannot create vec with given data.");
	vec->buffering_size = buffering_size;
	vec->size = 0;
	vec->type_size = type_size;
	vec->data = NULL;
	vec->allocated_size = buffering_size;
}

bool	vec_truncate(t_vec *vec)
{
	char	*new_data;
	
	assert((int[]){vec != NULL, 42}, "Null passed to vec_truncate.");
	new_data = malloc(vec->size * vec->type_size);
	if (!new_data)
		return (false);
	if (vec->data)
		ft_memcpy(new_data, vec->data, vec->size * vec->type_size);
	vec->allocated_size = vec->size;
	free(vec->data);
	vec->data = new_data;
	return (true);
}

void	vec_free(t_vec *vec)
{
	assert((int[]){vec != NULL, 42}, "Null passed to vec_free.");
	free(vec->data);
}

bool	vec_clone(t_vec *new, t_vec *old)
{
	assert((int[]){new != NULL, old != NULL, 42}, "Null passed to vec_clone.");
	if (new->data)
		new->data = malloc(old->size * old->type_size);
	else
		new->data = NULL;
	if (!new->data)
		return (false);
	if (old->data)
		ft_memcpy(new->data, old->data, old->size * old->type_size);
	new->allocated_size = old->size;
	new->size = old->size;
	new->buffering_size = old->buffering_size;
	new->type_size = old->type_size;
	return (true);
}

void	vec_null(t_vec *vec)
{
	assert((int[]){vec != NULL, 42}, "Null passed to vec_null.");
	vec->data = NULL;
	vec->size = 0;
	vec->type_size = 0;
	vec->buffering_size = 0;
	vec->allocated_size = 0;
}
