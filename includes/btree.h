/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 08:56:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/17 09:24:16 by lchamard         ###   ########.fr       */
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
}							t_operator;

typedef struct s_token_btree
{
	t_vec					tokens;
	t_operator				operator;
	struct s_token_btree	*left;
	struct s_token_btree	*right;
}							t_token_btree;

typedef struct s_cmd_btree
{
	t_cmd					cmds;
	t_operator				operator;
	struct s_token_btree	*left;
	struct s_token_btree	*right;
}			t_cmd_btree;

int		exec_binary_tree(t_cmd_btree *tree, char **env);
int 	exec_pipe(t_node_btree node, char **env);
t_pipex	cmd_to_pipex(t_cmd *cmd, char **env);

#endif
