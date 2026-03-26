/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:17:43 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/26 17:32:31 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_TO_CMD_H
# define VEC_TO_CMD_H

# include "btree.h"
# include "vec.h"

int		vec_to_cmd(t_btree_node *node, t_vec *expr, char **env);
void	grab_command(t_btree_node *node, t_vec *expr, char **env);
void	ft_append(char ***dest, const char *src);
size_t	ft_array_strlen(char **array_str);

#endif
