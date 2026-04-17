/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:51:43 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/14 11:59:24 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	list_new(void)
{
	t_list	new;

	new.first_cell = NULL;
	new.last_cell = NULL;
	new.size = 0;
	return (new);
}

bool	list_from_null_term_array(t_list *list, void **array, void (*free_func)(void *))
{
	t_u32	i;
	t_list	new;

	new = list_new();
	i = 0;
	while (array[i])
	{
		if (!list_push_back(&new, array[i]))
		{
			list_clear(&new, free_func);
			return (false);
		}
		i++;
	}
	*list = new;
	return (true);
}

bool	list_push_back(t_list *list, void *value)
{
	t_list_cell	*last;
	t_list_cell	*new;

	new = malloc(sizeof(t_list_cell));
	if (new)
	{
		new->next = NULL;
		new->value = value;
		last = list->last_cell;
		if (last)
		{
			new->previous = last;
			last->next = new;
		}
		else
		{
			new->previous = NULL;
			list->first_cell = new;
		}
		list->last_cell = new;
		list->size++;
		return (true);
	}
	return (false);
}

bool	list_push_front(t_list *list, void *value)
{
	t_list_cell	*new;
	t_list_cell	*previous;

	new = malloc(sizeof(t_list_cell));
	if (new)
	{
		new->value = value;
		new->previous = NULL;
		previous = list->first_cell;
		if (previous)
		{
			new->next = previous;
			previous->previous = new;
		}
		else
		{
			list->last_cell = new;
			new->next = NULL;
		}
		list->first_cell = new;
		list->size++;
		return (true);
	}
	return (false);
}
