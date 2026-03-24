/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:00:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/24 10:40:39 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_to_cmd.h"

size_t	ft_array_strlen(char **array_str)
{
	size_t	len;

	len = 0;
	while(array_str[len])
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

void	grab_command(t_btree_node *node, t_vec *expr, t_file files[2], char **env)
{
	t_cmd	*new_cmd;
	int		i;

	i = node->expr_start;
	new_cmd = ft_cmdnew();
	while (i < node->expr_end)
	{
		ft_append(&new_cmd->argv, vec_get(expr, i));
		if (!(new_cmd->name))
		{
			new_cmd->name = vec_get(expr, i);
			get_cmd_path(&new_cmd, env);
		}
		i++;
	}
	new_cmd->files = files;
	ft_cmdadd_back(&(node->cmds), &new_cmd);
}

int vec_to_cmd(t_btree_node *node, t_vec *expr, t_file files[2], char **env)
{
	grab_command(node, expr, files, env);
	return (0);
}
