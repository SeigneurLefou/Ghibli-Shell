/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:17:01 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/01 15:17:01 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator.h"

static void	check_pointer(t_smart_pointer *smart_pointer,
		t_smart_pointer **first, t_smart_pointer **last)
{
	if (smart_pointer->garbage)
	{
		if (smart_pointer->previous)
			smart_pointer->previous->next = smart_pointer->next;
		else
		{
			*first = smart_pointer->next;
			if (smart_pointer->next)
				smart_pointer->next->previous = NULL;
		}
		if (smart_pointer->next)
			smart_pointer->next->previous = smart_pointer->previous;
		else
		{
			*last = smart_pointer->previous;
			if (smart_pointer->previous)
				smart_pointer->previous->next = NULL;
		}
		free(smart_pointer);
	}
}

void	clean_freed_pointers(t_smart_pointer *smart_pointer,
		t_smart_pointer **first, t_smart_pointer **last)
{
	t_smart_pointer	*next;

	next = smart_pointer;
	while (next)
	{
		smart_pointer = next;
		next = smart_pointer->next;
		check_pointer(smart_pointer, first, last);
	}
}

void	free_every_smart_pointers(void *ptr)
{
	t_smart_pointer	*left;
	t_smart_pointer	*right;
	t_smart_pointer	*cursor;

	if (!ptr)
		return ;
	cursor = ptr;
	left = cursor->previous;
	right = cursor->next;
	free(cursor);
	while (left)
	{
		cursor = left;
		left = cursor->previous;
		free(cursor);
	}
	while (right)
	{
		cursor = right;
		right = cursor->next;
		free(cursor);
	}
}

void	create_smart_pointer(t_smart_pointer *smart_pointer,
		t_smart_pointer **first_mem_ptr, t_smart_pointer **last_mem_ptr,
		unsigned int tags)
{
	smart_pointer->garbage = false;
	smart_pointer->previous = *last_mem_ptr;
	smart_pointer->next = NULL;
	smart_pointer->tags = tags;
	if (!*first_mem_ptr)
		*first_mem_ptr = smart_pointer;
	if (!*last_mem_ptr)
		*last_mem_ptr = smart_pointer;
	else
	{
		(*last_mem_ptr)->next = smart_pointer;
		*last_mem_ptr = smart_pointer;
	}
}
