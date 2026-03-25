#ifndef PID_H
# define PID_H

typedef struct s_pid_list
{
	int		*pids;
	size_t	len;
}				t_pid_list;

void	pid_append(t_pid_list *pid_list)
{
	if (!len)
		len = 1;
	else
		len++;
}

#endif
