/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:43:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/15 16:48:49 by yben-dje         ###   ########.fr       */
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
int		bla_fn(int argc, char **argv);
bool	exec_builtin(t_cmd *cmds);
bool is_command_built_in(char *name);

int builtin_echo(int argc, char **argv);
int builtin_cd(int argc, char **argv);

#endif
