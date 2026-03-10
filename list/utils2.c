/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:44:20 by yben-dje          #+#    #+#             */
/*   Updated: 2026/02/23 13:17:01 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	list_clear_and_free(t_list *list, void (*free_func)(void *))
{
	if (list)
	{
		list_clear(list, free_func);
		free(list);
	}
}

static bool	push_back_and_check(t_list *new, void *result,
		void (*free_func)(void *))
{
	if (!list_push_back(new, result))
	{
		if (free_func)
			free_func(result);
		list_clear_and_free(new, free_func);
		return (false);
	}
	return (true);
}

int	list_map_duplicate(t_list *list, t_list **out, void *(*func)(void *),
		void (*free_func)(void *))
{
	unsigned int	i;
	void			*value;
	void			*result;
	t_list			*new;
	bool			encountered_nulls;

	new = list_new();
	if (!new)
		return (0);
	i = 0;
	encountered_nulls = false;
	while (i < list->size)
	{
		value = list_get_at_index(list, i);
		result = func(value);
		if (!result)
			encountered_nulls = true;
		if (!push_back_and_check(new, result, free_func))
			return (0);
		i++;
	}
	*out = new;
	if (encountered_nulls)
		return (2);
	return (1);
}

void	*list_to_flat_array(t_list *list, void *(*memcpy_func)(void *,
			const void *, size_t), size_t (*size_func)(const void *))
{
	size_t	size;
	t_u32	index;
	char	*dest;
	t_u32	cursor;
	void	*elem;

	index = 0;
	size = 0;
	while (index < list->size)
		size += size_func(list_get_at_index(list, index++));
	index = 0;
	dest = malloc(size + 1);
	if (!dest)
		return (NULL);
	cursor = 0;
	while (index < list->size)
	{
		elem = list_get_at_index(list, index);
		size = size_func(elem);
		memcpy_func(dest + cursor, elem, size);
		cursor += size;
		index++;
	}
	dest[size] = '\0';
	return (dest);
}

void	*list_as_array(t_list *list)
{
	void		**array;
	t_u32		index;
	t_iterator	iterator;

	array = malloc((list->size + 1) * sizeof(void **));
	if (!array)
		return (NULL);
	iterator = iterator_new(list, 0);
	index = 0;
	while (index < list->size)
		array[index++] = iterator_next(&iterator);
	array[index] = 0;
	return (array);
}
