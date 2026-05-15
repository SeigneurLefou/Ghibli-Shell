/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 23:01:52 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/15 23:03:46 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDS_H
# define EXPANDS_H

#include "vec.h"
#include "minishell.h"
#include "token.h"

typedef struct s_minishell	t_minishell;

bool	expand(t_vec *argv, t_token *token, t_minishell *minishell);

#endif

