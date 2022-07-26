/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvidon-n <joanavidon@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:09:37 by jvidon-n          #+#    #+#             */
/*   Updated: 2022/07/24 16:32:49 by jvidon-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int	ft_atoi(const char *ptr)
{
	int			s;
	long int	n;

	s = 1;
	n = 0;
	while (*ptr >= 48 && *ptr <= 57)
	{
		n = n * 10;
		n = n + ((int)*ptr - 48);
		ptr++;
	}
	return (n * s);
}

int	char_to_bin(int pid, unsigned int c)
{
	int		x;

	x = 0;
	while (x < 8)
	{
		if (c % 2 == 0 || c == 0)
		{
			kill(pid, SIGUSR1);
			sleep(2);
		}
		else
		{
			kill(pid, SIGUSR2);
			sleep(2);
		}
		c /= 2;
		x++;
	}
	return (0);
}

void	send_message(int sig)
{
	if (sig == SIGUSR2)
		exit(0);
}

int	main(int argc, char *argv[])
{
	pid_t				pid;
	unsigned int		c;

	if (argc != 3)
	{
		write(1, "Please, insert a pid and your message.\n", 39);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	while (*argv[2])
	{
		c = *argv[2];
		signal(SIGUSR1, send_message);
		char_to_bin(pid, c);
		argv[2]++;
	}
	signal(SIGUSR2, send_message);
	char_to_bin(pid, '\0');
}

/* int	char_to_bin(unsigned int c)
{
	int		x;

	x = 0;
	while (x < 8)
	{
		if (c % 2 == 0 || c == 0)
			write(1, "0", 1);
		else
		{
			write(1, "1", 1);
		}	
	c /= 2;
	x++;
	}
	return (0);
}

int main ()
{
	unsigned int c = 'a';
	printf("%d", char_to_bin(c));
}
a invertido = 10000110 */
