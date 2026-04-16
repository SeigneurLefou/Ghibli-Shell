#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>

static char parse_escape(char escaped_char)
{
	if (escaped_char == 'n')
		return ('\n');
	if (escaped_char == 't')
		return ('\t');
	if (escaped_char == 'v')
		return ('\v');
	if (escaped_char == 'e')
		return ('\e');
	if (escaped_char == 'a')
		return ('\a');
	else
		return (escaped_char);
}

void	echo_print(char **parts)
{
	unsigned int	index;
	unsigned int	index2;
	char c;

	index = 1;
	while (parts[index])
	{
		index2 = 0;
		while (parts[index][index2])
		{
			if (parts[index][index2 + 1] && parts[index][index2] == '\\')
				c = parse_escape(parts[index][++index2]);
			else
				c = parts[index][index2];
			write(1, &c, 1);
			index2++;
		}
        index++;
        if (parts[index])
            write(1, " ", 1);
    }
}

int	builtin_echo(int argc, char **argv)
{
	bool	newline;

	newline = true;
	if (argc >= 2)
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
	return (0);
}
