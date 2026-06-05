/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:30:28 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 16:12:06 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	handle_signal_default(int sig)
{
	g_signal = sig;
	close(0);
}

void	handle_signal_disabled(int sig)
{
	g_signal = sig;
	if (sig == SIGQUIT)
		write(2, "Quit\n", 6);
	else
		write(2, "\n", 1);
}
