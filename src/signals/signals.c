/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:30:28 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/03 13:07:23 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	handle_signal_default(int sig)
{
	g_signal = sig;
	close(0);
}

void	handle_signal_quit(int sig)
{
	g_signal = sig;
	write(2, "Quit", 5);
	close(0);
}
