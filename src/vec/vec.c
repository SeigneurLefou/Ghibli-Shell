/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:03:57 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/14 17:37:03 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

bool	vec_clone(t_vec *new, t_vec *old)
{
	new->data = malloc(old->size * old->type_size);
	if (!new->data)
		return (false);
	ft_memcpy(new->data, old->data, old->size * old->type_size);
	new->allocated_size = old->size;
	new->size = old->size;
	new->buffering_size = old->buffering_size;
	new->type_size = old->type_size;
	return (true);
}

void	vec_null(t_vec *vec)
{
	vec->data = NULL;
	vec->size = 0;
	vec->type_size = 0;
	vec->buffering_size = 0;
	vec->allocated_size = 0;
}

bool	vec_expand_and_free(t_vec *vec, t_vec *other)
{
	char			*new_data;
	unsigned int	alloc_size;

	if (vec->type_size != other->type_size)
		return (false);
	alloc_size = (vec->size + other->size + vec->buffering_size)
		* vec->type_size;
	new_data = malloc(alloc_size);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, vec->data, vec->size * vec->type_size);
	vec->allocated_size = vec->size + other->size + vec->buffering_size;
	ft_memcpy(new_data + vec->size * vec->type_size, other->data, other->size
		* other->type_size);
	vec->size += other->size;
	vec->data = new_data;
	vec_free(other);
	return (true);
}

char	*vec_to_cstring(t_vec vec)
{
	char	*str;

	str = malloc((vec.size + 1) * sizeof(char));
	if (!str)
		return (str);
	ft_memcpy(str, vec.data, vec.size * sizeof(char));
	str[vec.size] = 0;
	return (str);
}
