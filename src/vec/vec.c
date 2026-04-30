/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:04:45 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/30 15:33:15 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vec.h"
#include "utils.h"

bool	vec_init(t_vec *vec, size_t type_size, unsigned int buffering_size)
{
	assert((int[]){vec != NULL, type_size >= 0, buffering_size >= 0, 42}, "Cannot create vec with given data.");
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

bool	vec_append(t_vec *vec, void *data)
{
	char	*new_data;

	assert((int[]){vec != NULL, data != NULL, 42}, "Null passed to vec_append.");
	assert((int[]){vec->data != NULL, 42}, "Non-initialised vec.");
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
	
	assert((int[]){vec != NULL, 42}, "Null passed to vec_truncate.");
	assert((int[]){vec->data != NULL, 42}, "Non-initialised vec.");
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
	assert((int[]){vec != NULL, 42}, "Null passed to vec_free.");
	free(vec->data);
}

bool	vec_clone(t_vec *new, t_vec *old)
{
	assert((int[]){new != NULL, old != NULL, 42}, "Null passed to vec_clone.");
	assert((int[]){old->data != NULL, 42}, "Non-initialised vec.");
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
	assert((int[]){vec != NULL, 42}, "Null passed to vec_null.");
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

	assert((int[]){vec != NULL, other != NULL, 42}, "Null passed to vec_expand_and_free.");
	assert((int[]){vec->data != NULL, other->data != NULL, 42}, "Non-initialised vec.");
	assert((int[]){vec->type_size == other->type_size, 42}, "Typesize is different between vec and other.");
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

bool	vec_expand(t_vec *vec, t_vec *other)
{
	char			*new_data;
	unsigned int	alloc_size;

	assert((int[]){vec != NULL, other != NULL, 42}, "Null passed to vec_expand_and_free.");
	assert((int[]){vec->data != NULL, other->data != NULL, 42}, "Non-initialised vec.");
	assert((int[]){vec->type_size == other->type_size, 42}, "Typesize is different between vec and other.");
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
	return (true);
}

char	*vec_to_cstring(t_vec *vec)
{
	char	*str;

	assert((int[]){vec != NULL, 42}, "Null passed to vec_to_cstring.");
	assert((int[]){vec->data != NULL, 42}, "Non-initialised vec.");
	assert((int[]){vec->type_size == 1, 42}, "The data in vec is larger than a char.");
	str = malloc((vec->size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, vec->data, vec->size * sizeof(char));
	str[vec->size] = 0;
	return (str);
}

bool	str_to_vec_char(t_vec *vec, char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		vec_append(vec, &line[i]);
		i++;
	}
	return (true);
}

bool	vec_split(t_vec *vec, char *line, char sep)
{
	int		len;
	t_vec	sub_vec;
	char	*str;

	while (line && *line)
	{
		while (*line && *line == sep)
			line++;
		len = word_len(line, sep);
		if (!*line)
			return (true);
		vec_init(&sub_vec, sizeof(char), len);
		str = ft_substr(line, 0, len);
		str_to_vec_char(&sub_vec, str);
		if (!sub_vec.data)
			return (false);
		vec_append(vec, &sub_vec);
		vec_free(&sub_vec);
		line += len;
	}
	return (true);
}

char	**vec_vec_char_to_str_array(t_vec *vec)
{
	char	**str_array;
	size_t	i;

	str_array = malloc(sizeof(char *) * (vec->size + 1));
	i = 0;
	while (i < vec->size)
	{
		printf("argv[%lu] size of : %d, size of vec : %lu\n", i, (*(t_vec *)vec_get(vec, i)).type_size, sizeof(char));
		str_array[i] = vec_to_cstring(vec_get(vec, i));
		i++;
	}
	str_array[i] = NULL;
	return (str_array);
}
