/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 18:40:15 by yben-dje          #+#    #+#             */
/*   Updated: 2026/01/14 14:44:43 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	*list_pop_front(t_list *list)
{
	t_cell	*cell;
	void	*value;

	cell = list->first_cell;
	if (!cell)
		return (NULL);
	value = cell->value;
	list->first_cell = cell->next;
	if (list->first_cell)
		list->first_cell->previous = NULL;
	free(cell);
	list->size -= 1;
	if (!list->size)
		list->last_cell = NULL;
	return (value);
}

void	*list_pop_back(t_list *list)
{
	t_cell	*cell;
	void	*value;

	cell = list->last_cell;
	if (!cell)
		return (NULL);
	value = cell->value;
	list->last_cell = cell->previous;
	if (list->last_cell)
		list->last_cell->next = NULL;
	free(cell);
	list->size -= 1;
	if (!list->size)
		list->first_cell = NULL;
	return (value);
}

static void	*drop_cell(t_list *list, t_cell *cell)
{
	void	*value;

	if (cell->previous)
		cell->previous->next = cell->next;
	else
		list->first_cell = cell->next;
	if (cell->next)
		cell->next->previous = cell->previous;
	else
		list->last_cell = cell->previous;
	value = cell->value;
	list->size -= 1;
	free(cell);
	return (value);
}

void	*list_pop_at_index(t_list *list, t_u32 index)
{
	t_u32	i;
	t_cell	*cell;
	void	*value;

	if (!list->first_cell)
		return (NULL);
	cell = list->first_cell;
	i = 0;
	while (i < list->size)
	{
		if (i == index)
		{
			value = drop_cell(list, cell);
			return (value);
		}
		cell = cell->next;
		i++;
	}
	return (NULL);
}

void	list_clear(t_list *list, void (*free_func)(void *))
{
	void	*value;

	while (list->size)
	{
		value = list_pop_back(list);
		if (free_func)
			free_func(value);
	}
}
