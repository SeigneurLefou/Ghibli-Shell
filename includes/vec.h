/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:38:28 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/27 06:32:34 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <stdbool.h>
# include <stdlib.h>

typedef struct s_vec
{
	unsigned int	size;
	unsigned int	type_size;
	unsigned int	buffering_size;
	unsigned int	allocated_size;
	char			*data;
}					t_vec;

bool				vec_init(t_vec *vec, size_t type_size,
						unsigned int buffering_size);
void				*vec_get(t_vec *vec, unsigned int index);
bool				vec_append(t_vec *vec, void *data);
bool				vec_truncate(t_vec *vec);
void				vec_free(t_vec *vec);
bool				vec_clone(t_vec *new, t_vec *old);
bool				vec_expand_and_free(t_vec *vec, t_vec *other);
// Bro, this function is useful. Trust me
void				vec_null(t_vec *vec);
char				*vec_to_cstring(t_vec *vec);
bool				vec_split(t_vec *vec, char	*line, char character);
char				**vec_vec_char_to_str_array(t_vec *vec);
void				vec_set(t_vec *vec, unsigned int index, void *data);

#endif
