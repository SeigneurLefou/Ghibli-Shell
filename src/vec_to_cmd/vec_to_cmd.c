/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:17:27 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/09 09:34:30 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_to_cmd.h"

size_t	ft_array_strlen(char **array_str)
{
	size_t	len;

	len = 0;
	while (array_str && array_str[len])
		len++;
	return (len);
}

void	append_str_to_str_array(char ***dest, const char *src)
{
	size_t	len;
	char	**new_array;
	size_t	i;

	i = 0;
	if (!dest)
	{
		*dest = ft_calloc(2, sizeof(char *));
		(*dest)[0] = (char *)src;
		return ;
	}
	len = ft_array_strlen(*dest);
	new_array = ft_calloc(len + 2, sizeof(char *));
	while (i < len)
	{
		new_array[i] = (*dest)[i];
		i++;
	}
	new_array[i] = (char *)src;
	*dest = new_array;
}


void	vec_to_cmd(t_btree *tree)
{
	t_cmd	*new_cmd;
	size_t	i;
	t_token	*pointed_expr;

	i = tree->node.expr_start;
	new_cmd = ft_cmdnew();
	while (i <= tree->node.expr_end)
	{
		pointed_expr = (t_token *)vec_get(&tree->expr, i);
		/*if (pointed_expr && (ft_strcmp(pointed_expr->data, ">") && ft_strcmp(pointed_expr->data, ">>")
			&& ft_strcmp(pointed_expr, "<") && ft_strcmp(pointed_expr, "<<")))*/
		if (pointed_expr->type == token_type_plain)
		{
			append_str_to_str_array(&new_cmd->argv, vec_extract_str(pointed_expr->data)); // <- first error
			if (!(new_cmd->name))
			{
				new_cmd->name = vec_extract_str(pointed_expr->data);
				get_cmd_path(&new_cmd, tree->env);
			}
		}
		else
			i++;
		i++;
	}
	ft_cmdadd_back(&(tree->node.cmds), &new_cmd);
}
