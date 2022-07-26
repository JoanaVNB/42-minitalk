/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidon-n <joanavidon@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:10:39 by jvidon-n          #+#    #+#             */
/*   Updated: 2022/07/24 16:52:20 by jvidon-n         ###   ########.fr       */
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
	static unsigned int	i;
	static unsigned int	c;
	static pid_t		client_pid = 0;

	(void)context;
	client_pid = info->si_pid;
	if (i > 7)
	{
		i = 0;
		c = 0;
	}
	if (sig == SIGUSR2)
		c |= 1 << i;
	kill(client_pid, SIGUSR1);
	i++;
	if (i == 7)
		write(1, &c, 1);
}

int	main(void)
{
	struct sigaction	action;
	pid_t				pid;

	pid = getpid();
	write(1, "Server PID:", 11);
	ft_putnbr(pid);
	write(1, "\n", 1);
	sigemptyset(&action.sa_mask);
	action.sa_sigaction = handler_action;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}

/* void servidor(int c)
{
	static int	i;
	static char construindo;

	if (i > 7)
	{
		construindo = 0;
		i = 0;
	}
	if (c == 1)
		construindo |= 1 << i;
	printf("Chamado %d vezes\n", i);
	if (i == 7)
		 printf("%c\n", construindo);
	i++;
}
int main ()
{
	servidor(1);
  servidor(0);
  servidor(0);
  servidor(0);

  servidor(0);
  servidor(1);
  servidor(1);
  servidor(0);

  servidor(1);
  servidor(0);
  servidor(0);
  servidor(0);

  servidor(0);
  servidor(1);
  servidor(1);
  servidor(0);
} */