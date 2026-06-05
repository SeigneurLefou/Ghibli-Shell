/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:45:24 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 14:59:44 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <limits.h>

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 12) || c == ' ');
}

int	ft_atol_check_overflow(const char *nptr, bool *overflow)
{
	int		index;
	bool	negat;
	long	num;

	negat = false;
	index = 0;
	while (ft_isspace(nptr[index]))
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
		negat = nptr[index++] == '-';
	num = 0;
	while (ft_isdigit(nptr[index]))
	{
		num *= 10;
		num += nptr[index] - '0';
		if (num < 0 && ((negat && num != LONG_MIN) || !negat))
			*overflow = true;
		index++;
	}
	if (negat)
		return (-num);
	return (num);
}

char	*path_join(char *a, char *b)
{
	unsigned int	a_size;
	char			*path;

	a_size = ft_strlen(a);
	if (a[a_size - 1] == '/')
		path = ft_strjoin(a, b);
	else
	{
		path = ft_strjoin(a, "/");
		if (!path)
			return (false);
		path = ft_strjoin(path, b);
	}
	return (path);
}
