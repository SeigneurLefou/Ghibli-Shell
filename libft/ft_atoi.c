/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:09:18 by yben-dje          #+#    #+#             */
/*   Updated: 2025/10/21 11:48:05 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

int	ft_atoi(const char *nptr)
{
	int	index;
	int	negat;
	int	num;

	negat = 0;
	index = 0;
	while (is_whitespace(nptr[index]))
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
