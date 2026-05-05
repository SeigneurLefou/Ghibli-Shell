/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_runner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:35:12 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/01 15:35:34 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_RUNNER_H
# define FILE_RUNNER_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include "minishell.h"
# include "libft.h"
# include "getopt.h"
# include "error_manager.h"

typedef struct s_minishell	t_minishell;

bool	main_token(char *line, t_minishell *minishell);
char	*get_config_file_path(t_minishell *minishell, char *config_file);
bool	execute_file(char *filename, t_minishell *minishell);

#endif
