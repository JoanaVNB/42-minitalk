/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidon-n <joanavidon@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:10:39 by jvidon-n          #+#    #+#             */
/*   Updated: 2022/07/23 01:10:58 by jvidon-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> //para usar pid_t

void	ft_putnbr(unsigned int n)
{
	char			str[11];
	char			*ptr;
	int				c;

	c = 0;
	ptr = &str[0];
	while (n > 9)
	{
		*(ptr + c) = (n % 10) + 48;
		n = n / 10;
		c++;
	}
	*(ptr + c) = n + 48;
	while (c >= 0)
	{
		write(1, &*(ptr + c), 1);
		c--;
	}
}

void	handler_action(int sig, siginfo_t *info, void *context)
{
	static unsigned int	i = 0;
	static unsigned int	c =0;
	static pid_t			client_pid = 0;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	if ( i > 7)
	{
		i = 0;
		c = 0;
	}
	if (sig == SIGUSR2)
		c |= 1 << i;
	if (i == 7)
	{
		if (c == '\0')
			write(1, "\n", 1);
		write(1, &c, 1);
	}
	kill(client_pid, SIGUSR1);
	i++;
}

int	main(void)
{
	struct sigaction	action;
	pid_t	pid;

	pid = getpid();
	write(1, "Server PID:", 15);
	ft_putnbr(pid);
	write(1, "\n", 1);
	action.sa_sigaction = handler_action;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}