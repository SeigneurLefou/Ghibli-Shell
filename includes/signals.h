/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:29:16 by yben-dje          #+#    #+#             */
/*   Updated: 2026/06/05 16:14:23 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "minishell.h"

void	handle_signal_default(int sig);
void	handle_signal_disabled(int sig);
bool	setup_sig_handler(void);
bool	disable_sig_handler(void);

#endif