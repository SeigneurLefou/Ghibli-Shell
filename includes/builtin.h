/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:43:54 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/17 18:39:26 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "cmd.h"
# include "libft.h"
# include "minishell.h"
# include "vec.h"
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "environment_variables.h"

typedef struct s_minishell	t_minishell;
typedef int	(*t_builtin_function) (int argc, char **argv);

typedef struct s_function_node
{
	const char			*name;
	t_builtin_function	fn;
}						t_function_node;

char	*expand_variable(char *raw_line, char *pre_line, size_t *i, t_minishell *minishell);
char	*expand_line(t_minishell *minishell, char *raw_line);
bool	exec_builtin(t_cmd *cmds, t_env_variables_manager *env_manager);
bool is_command_built_in(char *name);

int						builtin_echo(int argc, char **argv);
int						builtin_cd(int argc, char **argv, t_env_variables_manager *env_manager);
int						builtin_pwd(int argc, char **argv);

#endif
