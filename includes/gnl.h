/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:47:21 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 08:52:44 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

char	*while_no_newline(int fd, char *buffer, char *line);
char	*join_line_with_previous_line(char	*buffer, char *line);
char	*give_next_line(char *buffer);
char	*get_next_line(int fd);

# endif
