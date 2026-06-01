/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchamard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:20:53 by lchamard          #+#    #+#             */
/*   Updated: 2026/06/01 15:21:21 by lchamard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#ifdef DEBUG

void	assert(int *checks, char *message)
{
	unsigned int	index;
	int				*no_problem_my_bro;

	index = 0;
	while (checks[index] != 42)
	{
		if (!checks[index])
		{
			write(2, "\x1B[31mAssertion failed: ", 24);
			write(2, message, ft_strlen(message));
			write(2, "\nFailed on assertion (first is 1) ", 35);
			ft_putnbr_fd(index + 1, 2);
			write(2,
				"\nIf you're in an evaluation, I'm very "
				"sorry but it'll probably stop here.\n"
				"Manual segfault incoming, please wait...\x1B[0m\n",
				120);
			no_problem_my_bro = (int *)0X0;
			checks[index] = 0[no_problem_my_bro];
		}
		index++;
	}
}
#else

void	assert(int *checks, char *message)
{
	(void)checks;
	(void)message;
}
#endif
