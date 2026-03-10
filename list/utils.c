/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 00:08:27 by yben-dje          #+#    #+#             */
/*   Updated: 2026/01/15 14:35:37 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

bool	list_map(t_list *list, bool (*func)(void **))
{
	unsigned int	i;
	t_cell			*cell;

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

t_list	*list_complete_duplicate(t_list *list, void *(duplicate_func)(void *),
		void (*free_func)(void *))
{
	t_list	*new;
	t_u32	i;
	void	*value;
	bool	result;

	new = list_new();
	if (!new)
		return (NULL);
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
			list_clear_and_free(new, free_func);
			return (NULL);
		}
	}
	return (new);
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
