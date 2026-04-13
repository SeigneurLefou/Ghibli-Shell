/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:55:07 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/13 14:41:20 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "btree.h"
# include "builtin.h"
# include "cmd.h"
# include "get_next_line.h"
# include "libft.h"
# include "list.h"
# include "pid.h"
# include "pipex.h"
# include "token.h"
# include "vec.h"
# include "vec_to_cmd.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include "error_manager.h"
# include "config_manager.h"
# include "file_runner.h"

char	*set_prompt_line(void);
void	handle_signal(int sig);
char	*handle_prompt(char *env[]);
bool	main_token(char *line, char *env[]);

#endif
