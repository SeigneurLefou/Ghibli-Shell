/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:17:27 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/16 17:00:05 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_to_cmd.h"
#include "builtin.h"

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
	char	*actual_argv;

	i = tree->node->expr_start;
	new_cmd = ft_cmdnew();
	while (i <= tree->node->expr_end)
	{
		pointed_expr = (t_token *)vec_get(&tree->expr, i);
		if (pointed_expr->type == token_type_plain)
		{
			actual_argv = expand_line(vec_to_cstring(pointed_expr->data));
			append_str_to_str_array(&new_cmd->argv, actual_argv);
			if (!(new_cmd->name))
			{
				new_cmd->argc = 0;
				new_cmd->name = actual_argv;
				if (!is_command_built_in(actual_argv))
					get_cmd_path(&new_cmd, tree->env);
			}
			new_cmd->argc++;
		}
		else
			i++;
		i++;
	}
	tree->node->cmds = new_cmd;
}
