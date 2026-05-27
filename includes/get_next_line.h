/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:46:47 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/18 20:28:12 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include "libft.h"
# include <fcntl.h>
# include <malloc.h>
# include <unistd.h>
# include "allocator.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void	safe_free(char **pointer);
int		contains(char *str, char c);
char	*gnl_strjoin(char *dst, const char *src, size_t line_size);

char	*get_next_line(int fd);

#endif