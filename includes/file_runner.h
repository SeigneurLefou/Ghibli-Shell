/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_runner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:35:12 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/09 15:41:58 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_RUNNER_H
# define FILE_RUNNER_H

#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include "libft.h"
#include "getopt.h"
#include "error_manager.h"

// Forwarding
bool	main_token(char *line, char *env[]);

bool execute_file(char *filename, char *env[]);

#endif