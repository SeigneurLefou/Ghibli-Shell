/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:43:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/23 19:21:39 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "btree.h"
# include "cmd.h"
# include "environment_variables.h"
# include "libft.h"
# include "minishell.h"
# include "pipex.h"
# include "token.h"
# include "vec.h"
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_minishell	t_minishell;
typedef int					(*t_builtin_function)(int argc, char **argv);
typedef struct s_btree		t_btree;
typedef struct s_token		t_token;

typedef struct s_function_node
{
	const char				*name;
	t_builtin_function		fn;
}							t_function_node;

char						*give_variable_content(t_token *raw_line, size_t *i,
								t_minishell *minishell, size_t expand_pointer);
char						*expand_line(t_token *raw_line,
								t_minishell *minishell);
bool						setup_and_exec_builtin(t_btree *tree, int files[2]);
int							exec_builtin(t_cmd *cmds, t_minishell *minishell);
bool						is_command_built_in(char *name);

int							builtin_echo(int argc, char **argv);
int							builtin_cd(int argc, char **argv,
								t_minishell *minishell);
int							builtin_pwd(int argc);
int							builtin_export(int argc, char **argv,
								t_minishell *minishell);
int							builtin_source(int argc, char **argv,
								t_minishell *minishell);
int							builtin_unset(int argc, char **argv,
								t_minishell *minishell);

#endif
