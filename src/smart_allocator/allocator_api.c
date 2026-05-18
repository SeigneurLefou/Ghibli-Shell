#include "allocator.h"

void	*mem_alloc(size_t size, void (*fail_callback)(void *),
		void *fail_callback_args)
{
	t_smart_pointer			*smart_pointer;
	static t_smart_pointer	*first_mem_ptr = NULL;
	static t_smart_pointer	*last_mem_ptr = NULL;

	clean_freed_pointers(first_mem_ptr, &first_mem_ptr, &last_mem_ptr);
	smart_pointer = malloc(sizeof(t_smart_pointer) + size);
	if (!smart_pointer)
	{
		free_every_smart_pointers(first_mem_ptr);
		if (fail_callback)
			fail_callback(fail_callback_args);
		return (NULL);
	}
	create_smart_pointer(smart_pointer, &first_mem_ptr, &last_mem_ptr);
	return ((void *)smart_pointer + sizeof(t_smart_pointer));
}

void	mem_free(void *ptr)
{
	t_smart_pointer	*smart_pointer;

	smart_pointer = ptr - sizeof(t_smart_pointer);
	smart_pointer->freed = true;
}

void	clean_all(void *ptr)
{
	free_every_smart_pointers(ptr - sizeof(t_smart_pointer));
}
