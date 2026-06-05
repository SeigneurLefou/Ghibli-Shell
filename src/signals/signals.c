/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:30:28 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 16:14:28 by yben-dje         ###   ########.fr       */
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

/* Based on the examples given at
https://circuitlabs.net/signal-handling-catching-signals-w-signal-sigaction */
bool	setup_sig_handler(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = handle_signal_default;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	if (sigaction(SIGTERM, &sa, NULL) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	signal(SIGQUIT, SIG_IGN);
	return (true);
}

bool	disable_sig_handler(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = handle_signal_disabled;
	if (sigemptyset(&sa.sa_mask) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("GhibliShell");
		return (false);
	}
	signal(SIGTERM, SIG_IGN);
	return (true);
}
