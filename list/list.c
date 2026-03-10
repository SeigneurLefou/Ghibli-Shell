/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:51:43 by yben-dje          #+#    #+#             */
/*   Updated: 2026/01/15 14:47:01 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./list.h"

t_list	*list_new(void)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->first_cell = NULL;
	new->last_cell = NULL;
	new->size = 0;
	return (new);
}

t_list	*list_from_null_term_array(void **array, void (*free_func)(void *))
{
	t_u32	i;
	t_list	*new;

	new = list_new();
	if (!new)
		return (NULL);
	i = 0;
	while (array[i])
	{
		if (!list_push_back(new, array[i]))
		{
			list_clear(new, free_func);
			free(new);
			return (NULL);
		}
		i++;
	}
	return (new);
}

bool	list_push_back(t_list *list, void *value)
{
	t_cell	*last;
	t_cell	*new;

	new = malloc(sizeof(t_cell));
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
	t_cell	*new;
	t_cell	*previous;

	new = malloc(sizeof(t_cell));
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
