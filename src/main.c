/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:53:16 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/24 08:57:39 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_btree_node *root = malloc(sizeof(t_btree_node));
	int i = 1;
	t_vec expr;
	root->expr_start = 0;
	root->expr_end = argc - 1;
	vec_init(&expr, sizeof(char *), 1);
	while (i < argc)
	{
		vec_append(&expr, argv[i]);
		i++;
	}
	vec_to_cmd(root, &expr, env);
	exec_binary_tree(root, env);
}
