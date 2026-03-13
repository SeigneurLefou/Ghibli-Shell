#ifndef CMD_H
# define CMD_H

#include "stdlib.h"
#include "libft.h"

typedef struct s_cmd
{
	char			**cmd_argv;
	char			*cmd_name;
	int				index;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}				t_cmd;

t_cmd	*ft_cmdnew(char *cmd_line, int index);
void	ft_cmdadd_front(t_cmd **cmd, t_cmd **new);
t_cmd	*ft_cmdlast(t_cmd *cmd);
t_cmd	*ft_cmdfirst(t_cmd *cmd);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd **new);
int		ft_cmdsize(t_cmd **cmd);
void	ft_cmdclear(t_cmd *cmd);
void	ft_cmdshow(t_cmd *cmd);
void	showallcmd(t_cmd **cmd);

#endif
