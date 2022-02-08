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
#define BYTES_IN_CHAR 4

int	set_signal_handler(int signal_no, \
	void (*handler_function)(int, siginfo_t *, void *));
int	send_one_char(int server_pid, unsigned long data);

int	g_busy;

void	signal_catcher(int signal_no, siginfo_t *info, void *hmm)
{
	g_busy = 0;
	(void) signal_no;
	(void) info;
	(void) hmm;
}

void	suicide(int signal_no, siginfo_t *info, void *hmm)
{
	(void) signal_no;
	(void) info;
	(void) hmm;
}

int	send_str(int server_id, char *in)
{
	while (*in)
		if (send_one_char(server_id, (unsigned long)*in++))
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	server_id;

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
	kill(server_id, SIGTERM);
	kill(getpid(), SIGTERM);
	return (EXIT_SUCCESS);
}

int	send_one_char(int server_pid, unsigned long data)
{
	unsigned long	bit_to_transfer;
	char			bit_len;
	int				signal;

	bit_len = 8 * BYTES_IN_CHAR;
	while (bit_len--)
	{
		g_busy = 1;
		bit_to_transfer = data & (1l << (8 * (BYTES_IN_CHAR) - 1));
		data = data << 1;
		signal = SIGUSR1;
		if (bit_to_transfer)
			signal = SIGUSR2;
		if (kill(server_pid, signal))
			return (1);
		if (g_busy)
			pause();
	}
	return (0);
}
