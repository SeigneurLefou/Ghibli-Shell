#include "exits.h"

void	memory_allocation_failed_error_exit(void)
{
	display_error_message("Memory allocation failed!");
	exit(1);
}

void	default_error_exit(void *data)
{
	(void)data;
	memory_allocation_failed_error_exit();
}

void	close_single_fd_error_exit(void *fd)
{
	close(*(int *)fd);
	memory_allocation_failed_error_exit();
}
