/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:52:38 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/16 13:58:45 by yben-dje         ###   ########.fr       */
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

t_env_variables_manager	env_variables_manager_new(void);
static char				*env_variables_manager_create_line(char *key,
							char *value);
bool					env_variables_manager_add_variable(t_env_variables_manager *env_variable_manager,
							char *key, char *value);
char					**env_variables_manager_get_env_compatible_variables_char_star_star(t_env_variables_manager *env_variable_manager);
char					*env_variable_manager_get_single(t_env_variables_manager *env_variable_manager,
							char *key);
bool					env_variable_manager_set(t_env_variables_manager *env_variable_manager,
							char *key, char *value);
bool					env_variable_manager_unset_key(t_env_variables_manager *env_variable_manager,
							char *key);
void					env_variables_manager_free(t_env_variables_manager *env_variable_manager);

#endif
