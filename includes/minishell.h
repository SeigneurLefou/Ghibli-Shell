/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 10:55:07 by lchamard          #+#    #+#             */
/*   Updated: 2026/03/27 17:04:17 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "btree.h"
# include "cmd.h"
# include "vec.h"
# include "gnl.h"
# include "libft.h"
# include "list.h"
# include "pipex.h"
# include "token.h"
# include "pid.h"
# include "vec_to_cmd.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*set_prompt_line(void);
void	handle_signal(int sig);
char	*handle_prompt(void);

#endif
