/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:19:19 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/23 12:25:46 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TTY_H
# define TTY_H

#include "vec.h"
#include "environment_variables.h"
# include "minishell.h"

typedef struct s_minishell t_minishell;

char	*render_prompt(char *base_prompt, t_minishell *minishell);

#endif