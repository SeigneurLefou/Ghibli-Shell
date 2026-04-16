/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 08:56:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/16 16:57:51 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include <stdbool.h>
# include <stdlib.h>
# include "vec.h"
# include "vec_to_cmd.h"
# include "token.h"
# include "cmd.h"
# include "pid.h"
# include "pipex.h"
# include "libft.h"

typedef struct s_pipex	t_pipex;

typedef enum e_operator
{
	operator_and,
	operator_or,
	operator_semicolon,
	operator_pipe,
	operator_none
}								t_operator;

typedef enum e_io_type
{
	io_type_infile,
	io_type_outfile,
	io_type_append_file,
	io_type_heredoc,
}		t_io_type;

typedef struct s_io_file
{
	t_io_type		type;
	unsigned int	file_name_token_index;
}		t_io_file;

typedef struct s_btree_node
{
	unsigned int		expr_start;
	unsigned int		expr_end;
	t_operator			operator;
	t_cmd				*cmds;
	t_vec				io_files;
	int					wstatus;
	struct s_btree_node	*left;
	struct s_btree_node	*right;
}								t_btree_node;

typedef struct s_btree
{
	t_vec				expr;
	struct s_btree_node	*node;
	char				**env;
}	t_btree;

t_pipex	cmd_to_pipex(t_cmd *cmd, char **env); // TODO: not defined
void	exec_cmd(t_btree *tree, int files[2], t_vec	*pid_list);
void	exec_pipeline(t_btree *tree, int files[2], t_vec *pid_list);
void	exec_right_pipeline(t_btree *tree, int files[2], t_vec *command_pid);
int		exec_binary_tree(t_btree *tree, int files[2]);
void	exec_right_tree(t_btree *tree, int files[2]);
int		cpy_btree_node(t_btree_node *new, t_btree_node *old);
int		cpy_btree(t_btree *new, t_btree *old);

#endif
