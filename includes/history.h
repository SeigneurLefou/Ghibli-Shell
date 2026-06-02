/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:21:15 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/01 14:21:16 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "minishell.h"

bool	add_file_to_history(char *line, int fd);
void	load_history_file(t_minishell *minishell, char *filename);
void	add_to_history_file(t_minishell *minishell, char *filename, char *line);
bool	read_file(char *filename);

#endif
