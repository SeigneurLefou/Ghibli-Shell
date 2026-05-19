/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:12:55 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/19 19:17:39 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "libft.h"
# include "token.h"
# include "vec.h"

void	show_error(t_vec *expr, char *msg, int index1, int index2);
void	display_error_message(char *msg);
void	memory_allocation_failed_error_exit(void);
void	default_error_exit(void *data);
void	close_single_fd_error_exit(void *fd);

#endif