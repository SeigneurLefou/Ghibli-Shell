/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:58:03 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/21 18:23:10 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_list_cell	t_list_cell;
typedef struct s_list		t_list;
typedef unsigned int		t_u32;

typedef struct s_list_cell
{
	t_list_cell				*next;
	t_list_cell				*previous;
	void					*value;
}							t_list_cell;

typedef struct s_list
{
	t_list_cell				*first_cell;
	t_list_cell				*last_cell;
	t_u32					size;
}							t_list;

typedef struct s_iterator
{
	t_list					*list;
	t_list_cell				*current_cell;
	t_u32					index;
}							t_iterator;

t_list						list_new(void);
bool						list_from_null_term_array(t_list *list,
								void **array, void (*free_func)(void *));
bool						list_push_back(t_list *list, void *value);
bool						list_push_front(t_list *list, void *value);
void						*list_get_at_index(t_list *list, t_u32 index);
t_list_cell					*list_get_cell_at_index(t_list *list, t_u32 index);

void						list_clear(t_list *list, void (*free_func)(void *));
void						*list_pop_back(t_list *list);
void						*list_pop_front(t_list *list);
void						*list_pop_at_index(t_list *list, t_u32 index);

bool						list_map(t_list *list, bool (*func)(void **));
bool						list_complete_duplicate(t_list *list, t_list *new,
								void *(duplicate_func)(void *),
								void (*free_func)(void *));
void						list_pop_front_free(t_list *list,
								void (*free_func)(void *));
int							lget_int(t_list *list, t_u32 index);
void						list_pop_at_free(t_list *list, t_u32 index,
								void (*free_func)(void *));

int							list_map_duplicate(t_list *list, t_list *out,
								void *(*func)(void *),
								void (*free_func)(void *));
void						*list_to_flat_array(t_list *list,
								void *(*memcpy_func)(void *, const void *,
									size_t), size_t (*size_func)(const void *));
void						*list_as_array(t_list *list);

t_iterator					iterator_new(t_list *list, t_u32 start);
void						*iterator_next(t_iterator *iterator);

#endif
