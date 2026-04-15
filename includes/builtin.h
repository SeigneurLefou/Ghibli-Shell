/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:43:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/15 11:19:41 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "vec.h"
# include "cmd.h"
# include <stdlib.h>

typedef int	(*t_builtin_function) (int argc, char **argv);

typedef struct s_function_node
{
	const char			*name;
	t_builtin_function	fn;
}				t_function_node;

char	*expand_variable(char *raw_line, char *pre_line, size_t *i);
char	*expand_line(char *raw_line);
bool	is_builtin(char *cmds, t_vec *builtin_list);
int		bla_fn(int argc, char **argv);
bool	exec_builtin(t_cmd *cmds, t_vec *builtin_list);
bool	init_builtin(t_vec *fn_vec, char *name_fn, t_builtin_function fn);
//bool	init_all_builtin(t_vec *fn_vec);

#endif
