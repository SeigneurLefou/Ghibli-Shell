/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:38:28 by yben-dje          #+#    #+#             */
/*   Updated: 2026/03/11 14:46:18 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "../libft/libft.h"
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

#endif
