/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:32:35 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/20 20:09:47 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "file_runner.h"

int	builtin_source(int argc, char **argv, t_minishell *minishell)
{
	int	result;

	if (argc != 2)
	{
		write(2, "Source needs one argument <path>.", 34);
		return (1);
	}
	minishell->internal_file_recursion++;
	if (minishell->internal_file_recursion > 100)
	{
		display_error_message("Max file recursion limit reachead!");
		return (1);
	}
	result = execute_file(argv[1], minishell);
	minishell->internal_file_recursion--;
	return (result);
}
