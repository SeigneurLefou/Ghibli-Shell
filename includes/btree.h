/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 08:56:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/30 14:25:22 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include <stdbool.h>
# include <stdlib.h>
# include "vec.h"
# include "token.h"
# include "cmd.h"
# include "pipex.h"
# include "files.h"
# include "libft.h"

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
} t_io_type;

typedef struct s_io_file
{
    t_io_type type;
    unsigned int file_name_token_index;
} t_io_file;

typedef struct s_btree_node
{
	unsigned int				expr_start;
	unsigned int				expr_stop;
	t_operator					operator;
	t_vec						io_files;
	t_cmd						*cmds;
	int							wstatus;
	int							pipe_fdo;
	struct s_btree_node	*left;
	struct s_btree_node	*right;
}								t_btree_node;

typedef struct s__btree
{
	t_vec						expr;
	struct s_btree_node	root_node;
}								t_btree;

int		exec_binary_tree(t_btree_node *tree, char **env);
int		exec_pipe(t_cmd *cmds, char **env);
int		exec_pipe(t_cmd *cmds, t_file files, char **env);
t_pipex	cmd_to_pipex(t_cmd *cmd, char **env);

#endif
