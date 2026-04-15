/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 09:38:42 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/15 11:26:38 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	exec_builtin(t_cmd *cmds, t_vec *builtin_list)
{
	t_function_node	fn_node;
	t_vec			*cpy_builtin_list;
	size_t			i;

	cpy_builtin_list = builtin_list;
	i = 0;
	while (i < builtin_list->size)
	{
		fn_node = *(t_function_node *)vec_get(cpy_builtin_list, i); 
		if (!ft_strcmp(cmds->name, fn_node.name))
		{
			fn_node.fn(cmds->argc, cmds->argv);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_builtin(char *cmds, t_vec *builtin_list)
{
	t_function_node	fn_node;
	t_vec			*cpy_builtin_list;
	size_t			i;

	cpy_builtin_list = builtin_list;
	i = 0;
	while (i < builtin_list->size)
	{
		fn_node = *(t_function_node *)vec_get(cpy_builtin_list, i); 
		if (!ft_strcmp(cmds, fn_node.name))
			return (true);
		i++;
	}
	return (false);
}

bool	init_builtin(t_vec *fn_vec, char *name_fn, t_builtin_function fn)
{
	t_function_node	fn_node;

	fn_node.name = name_fn;
	fn_node.fn = fn;
	vec_append(fn_vec, &fn_node);
	return (true);
}

/*
bool	init_all_builtin(t_vec *fn_vec)
{
	init_builin
}
*/
