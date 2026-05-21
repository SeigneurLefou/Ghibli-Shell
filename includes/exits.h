/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:54:13 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/21 18:21:03 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXITS_H
# define EXITS_H

# include <stdlib.h>
# include <unistd.h>

void	memory_allocation_failed_error_exit(void);
void	default_error_exit(void *data);
void	close_single_fd_error_exit(void *fd);

#endif