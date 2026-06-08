/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 12:19:19 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 20:02:02 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TTY_H
# define TTY_H

# include "environment_variables.h"
# include "minishell.h"
# include "vec.h"

typedef struct s_minishell	t_minishell;

char						*render_prompt(char *base_prompt,
								t_minishell *minishell);
char						*get_prompt_line(t_minishell *minishell);

void						process_condicionals(char *base_prompt,
								t_minishell *minishell, unsigned int *index,
								t_vec *rendered);
bool						expand_prompt_custom(t_vec *rendered, char c,
								t_minishell *minishell);
char						parse_escape(char escaped_char);
bool						can_escape(char *base_prompt, unsigned int index);

#endif