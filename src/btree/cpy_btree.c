/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_btree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:19:29 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/13 09:09:12 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

int	cpy_btree_node(t_btree_node *new, t_btree_node *old)
{
	new->expr_start = old->expr_start;
	new->expr_end = old->expr_end;
	new->operator = old->operator;
	new->cmds = old->cmds;
	new->wstatus = old->wstatus;
	if (old->left)
	{
		new->left = malloc(sizeof(t_btree_node));
		cpy_btree_node(new->left, old->left);
	}
	else
		new->left = NULL;
	if (old->right)
	{
		new->right = malloc(sizeof(t_btree_node));
		cpy_btree_node(new->right, old->right);
	}
	else
		new->right = NULL;
	return (EXIT_SUCCESS);
}

int	cpy_btree(t_btree *new, t_btree *old)
{
	t_btree_node	*cpy_node;

	new->env = old->env;
	new->expr = old->expr;
	new->node = malloc(sizeof(t_btree_node));
	cpy_node = old->node;
	cpy_btree_node(new->node, cpy_node);
	return (EXIT_SUCCESS);
}
