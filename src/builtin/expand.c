/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 06:45:58 by lchamard          #+#    #+#             */
/*   Updated: 2026/04/29 11:29:40 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*give_variable_content(t_token *token, size_t *i,
		t_minishell *minishell, size_t max_i)
{
	t_vec	var_name;
	char	*var_content;

	vec_init(&var_name, sizeof(char), 6);
	(*i)++;
	while (*i < token->data.size
		&& *i <= max_i)
	{
		vec_append(&var_name, vec_get(&token->data, *i));
		(*i)++;
	}
	var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
			vec_to_cstring(&var_name)));
	vec_free(&var_name);
	return (var_content);
}

char	*expand_tild(t_token *token, size_t *i, t_minishell *minishell)
{
	char	*var_content;

	var_content = NULL;
	if (*(char *)vec_get(&token->data, *i) == '~')
	{
		var_content = ft_strdup(env_variable_manager_get_single(&minishell->env_variables_manager,
				"HOME"));
		(*i)++;
	}
	printf("I after tild test : %lu\n", *i);
	return (var_content);
}

bool	add_str_to_vec_char(t_vec *new_line, char *var_content)
{
	int	i;

	i = 0;
	while (var_content[i])
	{
		if (!vec_append(new_line, &var_content[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	expand_split(t_vec *argv, t_vec *new_line, char *var_content)
{
	t_vec	var_split;
	size_t	j;

	vec_init(&var_split, sizeof(t_vec), 5);
	vec_split(&var_split, var_content, ' '); // On split le texte en un vec de vec de char ou chaque vec de char est un mot
	printf("SPLIT SIZE : %d\n", var_split.size);
	vec_expand(new_line, vec_get(&var_split, 0)); // On fusionne le premier "mot" avec la nouvelle ligne
	vec_append(argv, &new_line); // On ajoute la nouvelle ligne aux nouveaux argv
	vec_free(new_line);
	j = 1;
	while (j < var_split.size - 1)
	{
		vec_append(argv, vec_get(&var_split, j)); // On ajoute toutes les lignes sauf la dernière à l'argv
		j++;
	}
	printf("new_line size : %u, new_line pointer : %p, vec_split[j] : %p\n", new_line->size, new_line, vec_get(&var_split, j));
	vec_append(new_line, vec_get(&var_split, j)); // On remplace la nouvelle ligne par le derniere mot du split
	return (true);
}

bool	expand(t_vec *argv, t_token *token, t_minishell *minishell)
{
	size_t	i;
	t_vec	new_line;
	char	*var_content;
	size_t	expand_pointer;

	i = 0;
	vec_init(&new_line, sizeof(char), 20);
	expand_pointer = 0;
	while (i < token->data.size)
	{
		if (expand_pointer < token->expandable_scopes.size
			&& i == *(unsigned int *)vec_get(&token->expandable_scopes, expand_pointer))
		{
			expand_pointer++;
			var_content = expand_tild(token, &i, minishell);
			if (!var_content)
				var_content = give_variable_content(token, &i, minishell,
						(*(t_expand_data *)vec_get(&token->expandable_scopes, expand_pointer)).index); // Ici je récupère le contenu de la variable d'environnement
			if ((*(t_expand_data *)vec_get(&token->expandable_scopes, expand_pointer - 1)).allow_split) // S'il faut split cette condition vaut true
			{
				if (!expand_split(argv, &new_line, var_content))
					return (false);
			}
			else
				add_str_to_vec_char(&new_line, var_content); // Si il ne faut pas faire de split on ajoute le contenu de la variable d'env à la nouvelle ligne
			free(var_content);
			expand_pointer++;
		}
		else
		{
			vec_append(&new_line, vec_get(&token->data, i)); // Sinon on ajoute le caractere pointé à la nouvelle ligne
			i++;
		}
	}
	vec_append(argv, &new_line); // TODO : expand the last argv with new_line
	return (true);
}
