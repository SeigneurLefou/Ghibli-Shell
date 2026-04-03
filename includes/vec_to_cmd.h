/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:17:43 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/03 09:21:41 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_TO_CMD_H
# define VEC_TO_CMD_H

# include <stdbool.h>
# include <stdlib.h>
# include "token.h"
# include "btree.h"
# include "cmd.h"
# include "vec.h"
# include "libft.h"

typedef struct s_btree_node	t_btree_node;
typedef struct s_btree	t_btree;

void	vec_to_cmd(t_btree *tree);
void	ft_append(char ***dest, const char *src);
size_t	ft_array_strlen(char **array_str);

#endif
