/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 19:08:36 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/16 19:08:47 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#ifdef DEBUG
void	assert(bool checks[], unsigned int checks_count, char *message)
{
	unsigned int	index;

	index = 0;
	while (index < checks_count)
	{
		if (!checks[index])
		{
			write(2, "\x1B[31mAssertion failed: ", 24);
			write(2, message, ft_strlen(message));
            write(2, "\nFailed on assertion (first is 1) ", 35);
            ft_putnbr_fd(index + 1, 2);
			write(2,
					"\nIf you're in an evaluation, I'm very "
					"sorry but it'll probably stop here.\x1B[0m\n",
					79);
			exit(1);
		}
        index++;
	}
}
#else
void	assert(bool checks[], unsigned int checks_count, char *message)
{
    (void)checks;
    (void)checks_count;
    (void)message;
}
#endif
