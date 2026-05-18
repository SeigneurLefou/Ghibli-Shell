/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 18:53:10 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/18 19:08:36 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

/* Yeah, it's basically a garbage collector. Before that, we had so much leaks
 that our GhibliShell looked like the river spirit at the bathhouse in 
 Spirited Away.*/

typedef struct s_smart_pointer t_smart_pointer;

typedef struct s_smart_pointer
{
    bool freed;
    t_smart_pointer *next;
    t_smart_pointer *previous;
} t_smart_pointer;

/* Allocation functions.*/
void *mem_alloc(size_t size, void (* fail_callback)(void *), void *fail_callback_args);
void mem_free(void *ptr);
void clean_all(void *ptr);

/* Helpers functions. */
void clean_freed_pointers(t_smart_pointer *smart_pointer, t_smart_pointer **first, t_smart_pointer **last);
void free_every_smart_pointers(void *ptr);
void create_smart_pointer(t_smart_pointer *smart_pointer, t_smart_pointer **first_mem_ptr, t_smart_pointer **last_mem_ptr);