/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pyamcha <pyamcha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 10:49:34 by pyamcha           #+#    #+#             */
/*   Updated: 2021/07/27 11:31:52 by pyamcha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	conversion(char ch, int power, int pid)
{
	if (power > 0)
		conversion(ch / 2, power - 1, pid);
	if ((ch % 2) == 1)
	{
		if (kill(pid, SIGUSR1) == -1)
			while (1)
				continue ;
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
			while (1)
				continue ;
	}
	usleep(100);
}

int	ft_message(int server_pid, char *message)
{
	int	i;

	i = 0;
	while (message[i] != '\0')
	{
		conversion(message[i], 7, server_pid);
		i++;
	}
	write(1, "Signal was deliveried!\n", ft_strlen("Signal was deliveried!\n"));
	exit(0);
	return (0);
}

void	ft_signal(int signum, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	(void)siginfo;
	(void)signum;
}

int	main(int argc, char **argv)
{
	struct sigaction	signal;

	signal.sa_flags = SA_SIGINFO;
	signal.sa_sigaction = ft_signal;
	if ((sigaction(SIGUSR2, &signal, 0)) == -1)
		ft_error("Error: problems with sigaction!\n");
	if (argc == 3)
		ft_message(atoi(argv[1]), argv[2]);
	else
		ft_error("Error: wrong number of arguments!\n");
	while (1)
		pause();
	return (0);
}
