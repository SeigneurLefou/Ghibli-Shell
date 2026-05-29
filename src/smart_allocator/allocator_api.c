#include "allocator.h"
#include "exits.h"

void	*mem_alloc(size_t size, void (*fail_callback)(void *),
		void *fail_callback_args, unsigned int tags)
{
	t_smart_pointer			*smart_pointer;
	static t_smart_pointer	*first_mem_ptr = NULL;
	static t_smart_pointer	*last_mem_ptr = NULL;
	static bool				failed = false;
	
	if (failed)
		return (NULL);
	clean_freed_pointers(first_mem_ptr, &first_mem_ptr, &last_mem_ptr);
	smart_pointer = malloc(sizeof(t_smart_pointer) + size);
	if (!smart_pointer)
	{
		failed = true;
		free_every_smart_pointers(first_mem_ptr);
		if (fail_callback)
			fail_callback(fail_callback_args);
		return (NULL);
	}
	create_smart_pointer(smart_pointer, &first_mem_ptr, &last_mem_ptr, tags);
	return ((void *)smart_pointer + sizeof(t_smart_pointer));
}

void	mem_free(void *ptr)
{
	t_smart_pointer	*smart_pointer;

	if (!ptr)
		return ;
	smart_pointer = ptr - sizeof(t_smart_pointer);
	smart_pointer->garbage = true;
}

void	clean_all(void *ptr)
{
	free_every_smart_pointers(ptr - sizeof(t_smart_pointer));
}

bool	clear_garbage_collector(void)
{
	void	*ptr;

	ptr = mem_alloc(0, NULL, NULL, 0);
	if (!ptr)
		return (false);
	clean_all(ptr);
	return (true);
}

bool	mem_free_tags(unsigned int mask)
{
	t_smart_pointer	*next;
	t_smart_pointer	*smart_pointer;
	void			*ptr;

	ptr = mem_alloc(0, default_error_exit, NULL, 0);
	if (!ptr)
		return (false);
	smart_pointer = ptr - sizeof(t_smart_pointer);
	next = smart_pointer;
	while (next)
	{
		smart_pointer = next;
		next = smart_pointer->next;
		if (smart_pointer->tags & mask)
			smart_pointer->garbage = true;
	}
	return (true);
}
