/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:49 by                   #+#    #+#             */
/*   Updated: 2022/02/07 17:15:05 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <libft.h>

int	set_signal_handler(int signal_no, \
	void (*handler_function)(int, siginfo_t *, void *));
int	send_one_char(int server_pid, char data);
int	g_counter_received = 0;

void	signal_catcher(int signal_no, siginfo_t *info, void *hmm)
{
	g_counter_received++;
	(void) signal_no;
	(void) info;
	(void) hmm;
}

void	suicide(int signal_no, siginfo_t *info, void *hmm)
{
	g_counter_received++;
	(void) signal_no;
	(void) info;
	(void) hmm;
	exit(1);
}

int	send_str( int server_id, char *in)
{
	while (*in)
		if (send_one_char(server_id, *in++))
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int				server_id;

	if (argc != 3)
		return (1);
	server_id = ft_atoi(argv[2]);
	if (set_signal_handler(SIGUSR2, signal_catcher), \
		set_signal_handler(SIGUSR1, suicide))
		return (1);
	if (send_str(server_id, argv[1]) \
		|| send_one_char(server_id, NULLTERMIN))
	{
		ft_putendl_fd("transmission failed", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	send_one_char(int server_pid, char data)
{
	unsigned char	bit_to_transfer;
	int				counter;
	char			bit_len;

	bit_len = 8;
	while (bit_len--)
	{
		counter = g_counter_received;
		bit_to_transfer = data & 0b10000000;
		data = data << 0b00000001;
		if (bit_to_transfer)
		{
			if (kill(server_pid, SIGUSR2))
				return (1);
		}
		else
		{
			if (kill(server_pid, SIGUSR1))
				return (1);
		}
		usleep(10000);
		if (g_counter_received == counter)
			return (1);
	}
	return (0);
}
