/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:57:17 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/20 20:07:04 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_init(t_minishell *minishell)
{
    minishell->env_variables_manager = env_variables_manager_new();
    minishell->shell_level = 1;
    minishell->internal_file_recursion = 0;
}
