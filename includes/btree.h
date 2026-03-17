/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 08:56:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 17:30:49 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include "cmd.h"
# include "libft.h"
# include "pipex.h"
# include "token.h"
# include <stdbool.h>
# include <stdlib.h>

typedef enum e_operator
{
	operator_and,
	operator_or,
	operator_semicolon,
	operator_none,
}								t_operator;

typedef struct s_token_btree_node
{
	unsigned int				expr_start;
	unsigned int				expr_stop;
	t_operator					operator;
	struct s_token_btree_node	*left;
	struct s_token_btree_node	*right;
}								t_token_btree_node;

typedef struct s_token_btree
{
	t_vec						expr;
	struct s_token_btree_node	root_node;
}								t_token_btree;

typedef struct s_cmd_btree
{
	t_cmd						cmds;
	t_operator					operator;
	struct s_token_btree		*left;
	struct s_token_btree		*right;
}								t_cmd_btree;

int		exec_binary_tree(t_cmd_btree *tree, char **env);
int		exec_pipe(t_cmd cmds, char **env);
t_pipex	cmd_to_pipex(t_cmd *cmd, char **env);

#endif
