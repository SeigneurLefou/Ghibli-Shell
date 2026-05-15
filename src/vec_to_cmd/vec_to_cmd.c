/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:17:27 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/07 11:22:32 by lchamard         ###   ########.fr       */
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

void	append_str_to_array_str(char ***dest, const char *src)
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

void	expand_str(char ***dest, char **src)
{
	size_t	len;
	char	**new_array;
	size_t	i;
	size_t	j;

	new_array = malloc((ft_array_strlen(*dest) + ft_array_strlen(src) + 1));
	len = ft_array_strlen(*dest);
	i = 0;
	while (i < len)
	{
		new_array[i] = (*dest)[i];
		i++;
	}
	len = ft_array_strlen(src);
	j = 0;
	while (j < len)
	{
		new_array[i] = src[j];
		i++;
		j++;
	}
	new_array[i] = NULL;
	free(*dest);
	*dest = new_array;
}

void	vec_vec_free(t_vec *vec)
{
	unsigned int	i;

	i = 0;
	while (i < vec->size)
	{
		vec_free(vec_get(vec, i));
		i++;
	}
	vec_free(vec);
}

void	vec_to_cmd(t_btree *tree)
{
	t_cmd	*new_cmd;
	size_t	i;
	t_token	pointed_expr;
	t_vec	argv;

	new_cmd = ft_cmdnew();
	vec_init(&argv, sizeof(t_vec), 6);
	i = tree->node->expr_start;
	while (i <= tree->node->expr_end)
	{
		pointed_expr = *(t_token *)vec_get(&tree->expr, i);
		if (pointed_expr.type == token_type_plain)
			expand(&argv, &pointed_expr, tree->minishell);
		else
			i++;
		i++;
	}
	new_cmd->argc = argv.size;
	new_cmd->argv = vec_vec_char_to_str_array(&argv);
	new_cmd->name = new_cmd->argv[0];
	vec_vec_free(&argv);
	if (!is_command_built_in(new_cmd->name))
		get_cmd_path(new_cmd, tree->minishell);
	tree->node->cmds = new_cmd;
}
