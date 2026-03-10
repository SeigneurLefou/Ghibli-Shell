/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:31:47 by yben-dje          #+#    #+#             */
/*   Updated: 2026/01/28 23:40:27 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./list.h"

t_iterator	iterator_new(t_list *list, t_u32 start)
{
	t_iterator	iterator;

	iterator.index = start;
	iterator.current_cell = list_get_cell_at_index(list, start);
	iterator.list = list;
	return (iterator);
}

void	*iterator_next(t_iterator *iterator)
{
	void	*value;

	if (!iterator->current_cell || iterator->index >= iterator->list->size)
		return (NULL);
	iterator->index++;
	value = iterator->current_cell->value;
	iterator->current_cell = iterator->current_cell->next;
	return (value);
}
