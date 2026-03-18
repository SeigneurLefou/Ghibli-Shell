/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:00:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/18 11:34:21 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_to_cmd.h"

int vec_to_cmd(t_btree_node *node, t_vec *expr)
{
	int	i;
	t_cmd	new_node;

	i = node->expr_start;
	while (i <= node->expr_end || ft_strcmp(vec_get(expr, i), "|"))
	{
		if (ft_strcmp(vec_get(expr, i), ">"))
		{
			i++;
		}
		else if (ft_strcmp(vec_get(expr, i), ">>"))
		{
			i++;
		}
		else if (ft_strcmp(vec_get(expr, i), "<"))
		{
			i++;
		}
		else if (ft_strcmp(vec_get(expr, i), "<<"))
		{
			i++;
		}
		else
		{
			i = i;
		}
		i++;
	}
}
