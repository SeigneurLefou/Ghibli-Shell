/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:29:39 by yben-dje          #+#    #+#             */
/*   Updated: 2026/01/05 13:44:50 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	*list_get_at_index(t_list *list, t_u32 index)
{
	t_cell	*cell;

	cell = list_get_cell_at_index(list, index);
	if (cell)
		return (cell->value);
	return (NULL);
}

t_cell	*list_get_cell_at_index(t_list *list, t_u32 index)
{
	t_u32	i;
	t_cell	*cell;

	if (!list->first_cell)
		return (NULL);
	cell = list->first_cell;
	i = 0;
	while (i < list->size)
	{
		if (i == index)
			return (cell);
		cell = cell->next;
		i++;
	}
	return (NULL);
}
