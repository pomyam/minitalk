/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 10:50:51 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/27 11:32:03 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	my_handler(int signum, siginfo_t *siginfo, void *unused)
{
	static int	ascii = 0;
	static int	power = 0;

	(void)unused;
	if (signum == SIGUSR1)
		ascii += 1 << (7 - power);
	power += 1;
	if (power == 8)
	{
		write(1, &ascii, 1);
		power = 0;
		ascii = 0;
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			ft_error("Error: problem with signal!\n");
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	catch;

	(void)argv;
	if (argc != 1)
		ft_error("Error: wrong number of arguments!\n");
	write(1, "Server started!\nPID: ", ft_strlen("Server started!\nPID: "));
	write(1, ft_itoa(getpid()), ft_strlen(ft_itoa(getpid())));
	write(1, "\n", 1);
	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = my_handler;
	if ((sigaction(SIGUSR1, &catch, 0)) == -1)
		ft_error("Error: problen with sigaction!\n");
	if ((sigaction(SIGUSR2, &catch, 0)) == -1)
		ft_error("Error: problem with sigaction!\n");
	while (1)
		pause();
	return (0);
}
