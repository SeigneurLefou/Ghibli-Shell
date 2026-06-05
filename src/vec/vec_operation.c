/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:16:31 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/05 18:30:17 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	*vec_get(t_vec *vec, unsigned int index)
{
	if (index >= vec->size)
		return (NULL);
	return (vec->data + index * vec->type_size);
}

void	vec_set(t_vec *vec, unsigned int index, void *data)
{
	ft_memcpy(vec->data + index * vec->type_size, data, vec->type_size);
}

t_vec	vec_from_str(char *line)
{
	int		i;
	t_vec	vec;

	vec_init(&vec, sizeof(char), 32);
	i = 0;
	while (line && line[i])
	{
		vec_append(&vec, &line[i]);
		i++;
	}
	return (vec);
}
