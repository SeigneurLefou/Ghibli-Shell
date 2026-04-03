/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:16:54 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/02 19:16:02 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_MANAGER_H
# define CONFIG_MANAGER_H

# include "get_next_line.h"
# include "libft.h"

typedef enum e_config_parser_result
{
	t_config_parser_error_equal_not_found,
	t_config_parser_error_no_key,
    t_config_parser_error_memory_error,
	t_config_parser_error_success,
}	t_config_parser_result;

t_config_parser_result	config_parse_line(int file, char **key, char **value);

#endif