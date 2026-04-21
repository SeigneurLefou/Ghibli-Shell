/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:08:27 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/21 18:24:55 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

bool	list_map(t_list *list, bool (*func)(void **))
{
	unsigned int	i;
	t_list_cell			*cell;

	i = 0;
	while (i < list->size)
	{
		cell = list_get_cell_at_index(list, i);
		if (!func(&(cell->value)))
			return (false);
		i++;
	}
	return (true);
}

bool list_complete_duplicate(t_list *list, t_list *new, void *(duplicate_func)(void *),
		void (*free_func)(void *))
{
	t_u32	i;
	void	*value;
	bool	result;

	*new = list_new();
	i = 0;
	while (i++ < list->size)
	{
		value = list_get_at_index(list, i - 1);
		value = duplicate_func(value);
		result = list_push_back(new, value);
		if (!value || !result)
		{
			if (!result && free_func)
				free_func(value);
			list_clear(new, free_func);
			return (false);
		}
	}
	return (true);
}

void	list_pop_front_free(t_list *list, void (*free_func)(void *))
{
	void	*value;

	value = list_pop_front(list);
	free_func(value);
}

void	list_pop_at_free(t_list *list, t_u32 index, void (*free_func)(void *))
{
	void	*value;

	value = list_pop_at_index(list, index);
	free_func(value);
}

int	lget_int(t_list *list, t_u32 index)
{
	return (*(int *)list_get_at_index(list, index));
}
