/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:07:29 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/26 16:42:43 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef int	*t_as;

void		assert(int *checks, char *message);
bool		ft_isspace(char c);
int			ft_atol(const char *nptr);

#endif