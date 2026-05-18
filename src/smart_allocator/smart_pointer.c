#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_smart_pointer t_smart_pointer;

typedef struct s_smart_pointer
{
    bool freed;
    t_smart_pointer *next;
    t_smart_pointer *previous;
} t_smart_pointer;

void clean_freed_pointers(t_smart_pointer *smart_pointer, t_smart_pointer **first, t_smart_pointer **last)
{
    t_smart_pointer *next;

    next = smart_pointer;
    while (next)
    {
        smart_pointer = next;
        next = smart_pointer->next;
        if (smart_pointer->freed)
        {
            if (smart_pointer->previous)
                smart_pointer->previous->next = smart_pointer->next;
            else
            {
                *first = smart_pointer->next;
                smart_pointer->next->previous = NULL;
            }
            if (smart_pointer->next)
                smart_pointer->next->previous = smart_pointer->previous;
            else
            {
                *last = smart_pointer->previous;
                smart_pointer->previous->next = NULL;
            }
            free(smart_pointer);
        }
    }
}

void free_every_smart_pointers(t_smart_pointer *smart_pointer, void (* fail_callback)(void *), void *fail_callback_args)
{
    t_smart_pointer *left;
    t_smart_pointer *right;
    t_smart_pointer *cursor;

    if (!smart_pointer)
    {
        fail_callback(fail_callback_args);
        return ;
    }
    left = smart_pointer->previous;
    right = smart_pointer->next;
    while (left)
    {
        cursor = left;
        left = cursor->previous;
        free(cursor);
    }
    while (right)
    {
        cursor = right;
        right = cursor->previous;
        free(cursor);
    }
    fail_callback(fail_callback_args);
}

void *mem_alloc(size_t size, void (* fail_callback)(void *), void *fail_callback_args)
{
    t_smart_pointer *smart_pointer;
    static t_smart_pointer *first_mem_ptr = NULL;
    static t_smart_pointer *last_mem_ptr = NULL;

    clean_freed_pointers(first_mem_ptr, &first_mem_ptr, &last_mem_ptr);
    smart_pointer = malloc(sizeof(t_smart_pointer) + size);
    if (!smart_pointer)
    {
        free_every_smart_pointers(first_mem_ptr, fail_callback, fail_callback_args);
        return (NULL);
    }
    smart_pointer->freed = false;
    smart_pointer->previous = last_mem_ptr;
    smart_pointer->next = NULL;
    if (!first_mem_ptr)
        first_mem_ptr = smart_pointer;
    if (!last_mem_ptr)
        last_mem_ptr = smart_pointer;
    else
    {
        last_mem_ptr->next = smart_pointer;
        last_mem_ptr = smart_pointer;
    }
    return ((void *)smart_pointer + sizeof(t_smart_pointer));
}

void mem_free(void *ptr)
{
    t_smart_pointer *smart_pointer;

    smart_pointer = ptr - sizeof(t_smart_pointer);
    smart_pointer->freed = true;
}
