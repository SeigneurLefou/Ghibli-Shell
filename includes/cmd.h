/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:45:13 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/19 08:56:15 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stdlib.h>
# include <stdbool.h>
# include "libft.h"

typedef struct s_cmd
{
	char			*path;
	char			*name;
	char			**argv;
	char			*input_file;
	char			*output_file;
	bool			is_heredoc;
	int				open_mode;
	struct s_cmd	*next;
}				t_cmd;

t_cmd	*ft_cmdnew();
void	ft_cmdadd_front(t_cmd **cmd, t_cmd **new);
t_cmd	*ft_cmdlast(t_cmd *cmd);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd **new);
int		ft_cmdsize(t_cmd **cmd);
void	ft_cmdclear(t_cmd *cmd);
void	ft_cmdshow(t_cmd *cmd);
void	showallcmd(t_cmd **cmd);

#endif
