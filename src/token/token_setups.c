/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_setups.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:40:39 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 13:48:29 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	finish_tokeniser(t_token *current_token, t_vec *command)
{
	set_expand(current_token, false, false);
	if (current_token->type != token_type_void)
		vec_append(command, current_token);
}

void	setup_token(unsigned int *i, char *quote_char, t_token *current_token,
		t_vec *command)
{
	vec_init(command, sizeof(t_token), 4);
	*i = 0;
	*quote_char = 0;
	current_token->type = token_type_void;
	current_token->is_expand = false;
	current_token->no_skip = false;
}
