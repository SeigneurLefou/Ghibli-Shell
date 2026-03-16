/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 08:46:18 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/16 09:19:41 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_binary_tree(t_btree *tree)
{
	int	wstatus_left;
	int	wstatus_right;

	if (!tree->left && !tree->right)
		wstatus_left = exec_pipe(tree->node);
	if (tree->left)
		wstatus_left = exec_binary_tree(tree->left)
	if (!wstatus_left && tree->node->operator && tree->right)
		wstatus_right = exec_binary_tree(tree->right)
	if (wstatus_left && !tree->node->operator && tree->right)
		wstatus_right = exec_binary_tree(tree->right)
	if (tree->node->operator)
		return (wstatus_left & wstatus_right)
	else
		return (wstatus_left | wstatus_right)
}
