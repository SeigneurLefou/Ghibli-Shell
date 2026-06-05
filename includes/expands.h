/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 23:01:52 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 20:25:45 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDS_H
# define EXPANDS_H

# include "minishell.h"
# include "token.h"
# include "vec.h"

typedef struct s_expand_data	t_expand_data;
typedef struct s_minishell		t_minishell;
struct							s_expander_data
{
	t_token						*token;
	t_expand_data				*expand_data;
	char						*var_content;
	size_t						exp_data_i;
	size_t						char_index;
	bool						skip_token;
	t_vec						expanded_token;
};

bool							expand(t_vec *argv, t_token *token,
									t_minishell *minishell);
char							*give_variable_content(t_token *token,
									size_t *i, t_minishell *minishell,
									size_t max_i);
char							*expand_tild(t_token *token, size_t *i,
									t_minishell *minishell);
bool							file_matches_filter(t_vec *filter, char *name);
bool							query_files_in_dir(t_vec *out, char *path,
									t_vec *filter);
bool							handle_wildcard(t_vec *argv, t_token *token,
									t_minishell *minishell);
bool							add_str_to_vec_char(t_vec *expanded_token,
									char *var_content);
unsigned int					get_check_start(char *name, char *wildcard,
									char *str_filter);
bool							expand_variable(struct s_expander_data *data,
									t_vec *argv, t_minishell *minishell,
									t_token *token);
bool							setup_expander(struct s_expander_data *exp_data,
									t_vec *argv, t_token *token,
									t_minishell *minishell);
void							add_remaining_token(
									struct s_expander_data *exp_data,
									t_vec *argv, t_token *token);
bool							expand_split(t_vec *argv, t_vec *expanded_token,
									char *var_content, bool *can_skip_token);
#endif
