/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:17:43 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/15 23:05:44 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_TO_CMD_H
# define VEC_TO_CMD_H

# include <stdbool.h>
# include <stdlib.h>
# include "token.h"
# include "btree.h"
# include "builtin.h"
# include "cmd.h"
# include "vec.h"
# include "libft.h"
# include "expands.h"

typedef struct s_btree_node	t_btree_node;
typedef struct s_btree	t_btree;

void	vec_to_cmd(t_btree *tree);
void	expand_str(char ***dest, char **src);
size_t	ft_array_strlen(char **array_str);

#endif
