/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 08:56:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/20 08:36:17 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include <stdbool.h>
# include <stdlib.h>
# include "token.h"
# include "cmd.h"
# include "pipex.h"
# include "libft.h"

typedef enum e_operator
{
	operator_and,
	operator_or,
	operator_semicolon,
	operator_none,
}								t_operator;

typedef struct s_btree_node
{
	unsigned int				expr_start;
	unsigned int				expr_end;
	t_operator					operator;
	t_cmd						*cmds;
	struct s_btree_node	*left;
	struct s_btree_node	*right;
}								t_btree_node;

typedef struct s__btree
{
	t_vec						expr;
	struct s_btree_node	root_node;
}	t_btree;

int		exec_binary_tree(t_btree_node *tree, char **env);
int		exec_pipe(t_cmd *cmds, char **env);
t_pipex	cmd_to_pipex(t_cmd *cmd, char **env);

#endif
