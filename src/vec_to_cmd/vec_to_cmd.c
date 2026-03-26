/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:17:27 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/26 09:39:31 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_to_cmd.h"

size_t	ft_array_strlen(char **array_str)
{
	size_t	len;

	len = 0;
	while (array_str[len])
		len++;
	return (len);
}

void	ft_append(char ***dest, const char *src)
{
	size_t	len;
	char	**new_array;
	size_t	i;

	i = 0;
	if (!(*dest))
	{
		*dest = ft_calloc(2, sizeof(char *));
		*dest[0] = (char *)src;
		return ;
	}
	len = ft_array_strlen(*dest);
	new_array = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		new_array[i] = *dest[i];
		i++;
	}
	new_array[i] = (char *)src;
	*dest = new_array;
}

void	grab_command(t_btree_node *node, t_vec *expr, char **env)
{
	t_cmd	*new_cmd;
	int		i;
	char	*pointed_expr;

	i = node->expr_start;
	new_cmd = ft_cmdnew();
	while (i < node->expr_end)
	{
		pointed_expr = vec_get(expr, i);
		if (ft_strcmp(pointed_expr, ">") && ft_strcmp(pointed_expr, ">>")
			&& ft_strcmp(pointed_expr, "<")
			&& ft_strcmp(pointed_expr, "<<"))
		{
			ft_append(&new_cmd->argv, pointed_expr);
			if (!(new_cmd->name))
			{
				new_cmd->name = pointed_expr;
				get_cmd_path(&new_cmd, env);
			}
		}
		else
			i++;
		i++;
	}
	ft_cmdadd_back(&(node->cmds), &new_cmd);
}

int	vec_to_cmd(t_btree_node *node, t_vec *expr, char **env)
{
	grab_command(node, expr, files, env);
	return (0);
}
