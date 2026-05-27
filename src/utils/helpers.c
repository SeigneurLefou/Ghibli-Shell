/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:45:24 by yben-dje          #+#    #+#             */
/*   Updated: 2026/05/26 16:42:45 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 12) || c == ' ');
}

int	ft_atol(const char *nptr)
{
	int		index;
	bool	negat;
	long	num;

	negat = 0;
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
		index++;
	}
	if (negat)
		return (-num);
	return (num);
}
