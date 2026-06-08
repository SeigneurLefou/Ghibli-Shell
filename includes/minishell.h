/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:55:07 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/08 15:14:24 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "btree.h"
# include "builtin.h"
# include "cmd.h"
# include "environment_variables.h"
# include "error_manager.h"
# include "file_runner.h"
# include "get_next_line.h"
# include "ghiblirc_default.h"
# include "history.h"
# include "libft.h"
# include "list.h"
# include "pipex.h"
# include "signals.h"
# include "token.h"
# include "tty.h"
# include "vec.h"
# include "vec_to_cmd.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_minishell
{
	t_env_variables_manager		env_variables_manager;
	int							shell_level;
	int							internal_file_recursion;
	bool						request_exit;
	int							stdin_save;
	int							last_status;
}								t_minishell;

void							handle_prompt(t_minishell *minishell);
bool							main_token(char *line, t_minishell *minishell);
void							minishell_init(t_minishell *minishell);
void							increment_shell_lvl(t_minishell *minishell);
void							load_config_file(t_minishell *minishell,
									char *config_file);

void							increment_shell_lvl(t_minishell *minishell);
bool							setup_minishell(t_minishell *minishell,
									char *env[]);

#endif
