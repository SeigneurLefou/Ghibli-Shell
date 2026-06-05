/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expds_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:02:53 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 15:07:12 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expands.h"

static bool	setup_expand_split(char *var_content, t_vec *var_split,
		t_vec *expanded_token)
{
	vec_init(var_split, sizeof(t_vec), 5);
	vec_split_space(var_split, var_content);
	if (!var_split->size)
		return (false);
	if (!ft_isspace(var_content[0]))
		vec_expand(expanded_token, vec_get(var_split, 0));
	return (true);
}

bool	expand_split(t_vec *argv, t_vec *expanded_token, char *var_content,
		bool *can_skip_token)
{
	t_vec	var_split;
	size_t	j;
	bool	split_at_end;

	if (!var_content)
		return (true);
	if (!setup_expand_split(var_content, &var_split, expanded_token))
		return (false);
	split_at_end = ft_isspace(var_content[ft_strlen(var_content) - 1]);
	*can_skip_token = split_at_end;
	if (var_split.size > 1)
	{
		if (expanded_token->size)
			vec_append(argv, expanded_token);
		vec_init(expanded_token, sizeof(char), 20);
		j = !ft_isspace(var_content[0]);
		while (j < var_split.size - !split_at_end)
			vec_append(argv, vec_get(&var_split, j++));
		if (!split_at_end)
			vec_expand(expanded_token, vec_get(&var_split, j));
	}
	vec_free(&var_split);
	return (!var_split.failed);
}
