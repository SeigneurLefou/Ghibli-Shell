/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:12:55 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/02 11:18:42 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

#include "vec.h"
#include "token.h"
#include "libft.h"

void show_error(t_vec *expr, char *msg, int index1, int index2);
void display_error_message(char *msg);

#endif