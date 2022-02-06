#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <time.h>

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

int send_str( int server_id, char *in)
{
	while (*in)
		if (send_one_char(server_id, *in++))
			return (1);
	return (0);
}

int main (int argc, char** argv)
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
    return EXIT_SUCCESS;
	(void) argc;
	(void) argv;
	(void) server_id;
}

int	send_one_char(int server_pid, char data)
{
	unsigned char	bit_to_transfer;
	int				counter;
	char			bit_len = 8;
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
		usleep(100);
		if (g_counter_received == counter)
			usleep(10000);
		if (g_counter_received == counter)
		{
			ft_putendl_fd("no answer received", 2);
			exit(2);
			return (1);
		}
	}
	return (0);
}
