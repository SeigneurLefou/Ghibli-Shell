#include "libft.h"
#include <stdbool.h>

void	echo_print(char **parts)
{
	unsigned int	index;

	index = 1;
	while (parts[index])
	{
		write(1, parts[index], ft_strlen(parts[index]));
        index++;
        if (parts[index])
            write(1, " ", 1);
    }
}

int	builtin_echo(char **argv)
{
	bool	newline;

	newline = true;
	if (argv[1])
	{
		if (!ft_strncmp(argv[1], "-n", 2))
		{
			echo_print(argv + 1);
			newline = false;
		}
		else
			echo_print(argv);
	}
	else
		echo_print(argv);
	if (newline)
		write(1, "\n", 1);
    exit(0);
}
