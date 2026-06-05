/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:16:20 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/05 16:27:30 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exits.h"
#include "vec.h"

bool	vec_append(t_vec *vec, void *data)
{
	char	*new_data;

	if (vec->failed)
		return (false);
	if (!vec->data || vec->size >= vec->allocated_size)
	{
		new_data = mem_alloc((vec->allocated_size + vec->buff_size)
				* vec->type_size, default_error_exit, NULL, 0b1);
		if (!new_data)
		{
			vec->failed = true;
			return (false);
		}
		if (vec->data)
			ft_memcpy(new_data, vec->data, vec->allocated_size
				* vec->type_size);
		vec->allocated_size += vec->buff_size;
		mem_free(vec->data);
		vec->data = new_data;
	}
	ft_memcpy(vec->data + vec->size * vec->type_size, data, vec->type_size);
	vec->size++;
	return (false);
}

void	vec_expand_and_free(t_vec *vec, t_vec *other)
{
	char			*new_data;
	unsigned int	alloc_size;

	if (vec->failed)
		return ;
	alloc_size = (vec->size + other->size + vec->buff_size) * vec->type_size;
	new_data = mem_alloc(alloc_size, default_error_exit, NULL, 0b1);
	if (!new_data)
	{
		vec->failed = true;
		return ;
	}
	if (vec->data)
		ft_memcpy(new_data, vec->data, vec->size * vec->type_size);
	vec->allocated_size = vec->size + other->size + vec->buff_size;
	if (other->data)
		ft_memcpy(new_data + vec->size * vec->type_size, other->data,
			other->size * other->type_size);
	vec->size += other->size;
	vec->data = new_data;
	vec_free(other);
}

void	vec_expand(t_vec *vec, t_vec *other)
{
	char			*new_data;
	unsigned int	alloc_size;

	if (vec->failed)
		return ;
	alloc_size = (vec->size + other->size + vec->buff_size) * vec->type_size;
	new_data = mem_alloc(alloc_size, default_error_exit, NULL, 0b1);
	if (!new_data)
		return ;
	if (vec->data)
		ft_memcpy(new_data, vec->data, vec->size * vec->type_size);
	vec->allocated_size = vec->size + other->size + vec->buff_size;
	if (other->data)
		ft_memcpy(new_data + vec->size * vec->type_size, other->data,
			other->size * other->type_size);
	vec->size += other->size;
	vec->data = new_data;
}

/* Could be optimized but hey! Blackhole is comming!*/
void	vec_expand_from_str(t_vec *vec, char *str)
{
	unsigned int	index;

	index = 0;
	while (str[index])
	{
		vec_append(vec, &str[index]);
		index++;
	}
}
