#include "exits.h"
# include "error_manager.h"
#include <unistd.h>
#include <sys/stat.h>

void close_all_fds()
{
    struct stat buf;
    unsigned int index;

    index = 3;
    while (index < 1024)
    {
        if (fstat(index, &buf) != -1) {
            close(index);
        }
        index++;
    }
}

void	memory_allocation_failed_error_exit(void)
{
	display_error_message("Memory allocation failed!");
	close_all_fds();
	exit(1);
}

void	default_error_exit(void *data)
{
	(void)data;
	memory_allocation_failed_error_exit();
}
