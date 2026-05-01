#ifndef HISTORY_H
# define HISTORY_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "minishell.h"

void	load_history_file(t_minishell *minishell, char *filename);
void	add_to_history_file(t_minishell *minishell, char *filename, char *line);
bool	read_file(char *filename);

#endif
