/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:00:48 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/19 11:18:40 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_to_cmd.h"

size_t		ft_array_strlen(char **array_str)
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
		ft_strcpy((*dest)[0], src);
		return ;
	}
	len = ft_array_strlen(*dest);
	new_array = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		new_array[i] = (*dest)[i];
		i++;
	}
	ft_strcpy(new_array[i], src);
	*dest = new_array;
}

int vec_to_cmd(t_btree_node *node, t_vec *expr)
{
	int	i;
	t_cmd	*new_cmd;

	i = node->expr_start;
	new_cmd = ft_cmdnew();
	while (i <= node->expr_end || ft_strcmp(vec_get(expr, i), "|"))
	{
		if (ft_strcmp(vec_get(expr, i), ">"))
		{
			new_cmd->input_file = vec_get(expr, ++i);
		}
		else if (ft_strcmp(vec_get(expr, i), ">>"))
		{
			new_cmd->is_heredoc = true;
			new_cmd->input_file = vec_get(expr, ++i);
		}
		else if (ft_strcmp(vec_get(expr, i), "<"))
		{
			new_cmd->output_file = vec_get(expr, ++i);
			new_cmd->open_mode = O_TRUNC;
		}
		else if (ft_strcmp(vec_get(expr, i), "<<"))
		{
			new_cmd->output_file = vec_get(expr, ++i);
			new_cmd->open_mode = O_APPEND;
		}
		else
			ft_append(&new_cmd->argv, vec_get(expr, i));
		i++;
	}
	node->cmds = new_cmd;
	return (0);
}
