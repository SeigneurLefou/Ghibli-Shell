/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:52:38 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/18 10:02:05 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVIRONMENT_VARIABLES_H
# define EVIRONMENT_VARIABLES_H

# include "libft.h"
# include "list.h"

typedef struct s_env_variables_manager
{
	t_list				variables;
}						t_env_variables_manager;

t_env_variables_manager	env_variables_new(void);
bool					env_variables_add(t_env_variables_manager *env_variable_manager,
							char *key, char *value);
char					**env_variables_get_env(t_env_variables_manager *env_variable_manager);
char					*env_variables_get(t_env_variables_manager *env_variable_manager,
							char *key);
bool					env_variables_set(t_env_variables_manager *env_variable_manager,
							char *key, char *value);
bool					env_variables_unset_key(t_env_variables_manager *env_variable_manager,
							char *key);
void					env_variables_free(t_env_variables_manager *env_variable_manager);
bool					env_variables_add_from_env(t_env_variables_manager *env_variable_manager,
							char **env);
bool					env_variables_exists(t_env_variables_manager *env_variable_manager,
							char *key);
bool					env_variables_set_raw(t_env_variables_manager *env_variable_manager,
							char *line);
char					*env_variables_get_raw(t_env_variables_manager *env_variable_manager,
							char *key);

#endif
