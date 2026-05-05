/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:55:07 by lchamard          #+#    #+#             */
/*   Updated: 2026/05/01 15:37:16 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "btree.h"
# include "builtin.h"
# include "cmd.h"
# include "config_manager.h"
# include "environment_variables.h"
# include "error_manager.h"
# include "file_runner.h"
# include "get_next_line.h"
# include "ghiblirc_default.h"
# include "libft.h"
# include "list.h"
# include "pid.h"
# include "pipex.h"
# include "token.h"
# include "history.h"
# include "vec.h"
# include "vec_to_cmd.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include "tty.h"
# include "signals.h"

extern int g_signal;

typedef struct s_minishell
{
	t_env_variables_manager	env_variables_manager;
	int						shell_level;
	int						internal_file_recursion;
	bool					request_exit;
}							t_minishell;

void						handle_prompt(t_minishell *minishell);
bool						main_token(char *line, t_minishell *minishell);
void						minishell_init(t_minishell *minishell);
void						increment_shell_lvl(t_minishell *minishell);
void						load_config_file(t_minishell *minishell,
								char *config_file);

#endif
