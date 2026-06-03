/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:52:37 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 19:17:32 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/* From left to right */
void	parse_leaf(t_vec *expr, t_btree_node *node)
{
	t_token			*token;
	t_io_file		file;
	unsigned int	index;

	index = node->expr_start;
	if (!node->io_files.data)
		vec_init(&node->io_files, sizeof(t_io_file), 2);
	while (index < node->expr_end)
	{
		token = (t_token *)vec_get(expr, index);
		if (!set_io_delimiters_type(token, &file))
		{
			index++;
			continue ;
		}
		index++;
		file.filename_token_i = index;
		vec_append(&node->io_files, &file);
		index++;
	}
}

void	set_leaf(t_vec *expr, t_btree_node *node)
{
	node->expr_start = node->expr_start;
	node->expr_end = node->expr_end;
	node->operator = operator_none;
	node->left = NULL;
	node->right = NULL;
	parse_leaf(expr, node);
}
