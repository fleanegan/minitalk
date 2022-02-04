#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <time.h>

int set_signal_handler(int signal_no, void (*handler_function)(int, siginfo_t *, void *));

int send_one_char(int server_pid, char data);

int g_counter_received = 0;

void	signal_catcher(int signal_no, siginfo_t *info, void *hmm)
{
	g_counter_received++;
	(void) signal_no;
	(void) info;
	(void) hmm;
	//kill(info->si_pid, SIGUSR1);
}

void	suicide(int signal_no, siginfo_t *info, void *hmm)
{
	printf("sent %d signals\n", g_counter_received);
	(void) signal_no;
	(void) info;
	(void) hmm;
	//kill(getpid(), SIGTERM);
}

int main (int argc, char** argv)
{
	int				server_id;


	server_id = ft_atoi(argv[1]);
	if (set_signal_handler(SIGUSR2, signal_catcher), \
		set_signal_handler(SIGUSR1, suicide))
		return (1);
	send_one_char(server_id, 'B');
	send_one_char(server_id, 'Y');
	send_one_char(server_id, 'O');
	send_one_char(server_id, 'B');
	printf("the client received %d signals\n", g_counter_received);
	kill(server_id, SIGTERM);
	kill(getpid(), SIGTERM);
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
//		printf("bit: %d\n", bit_to_transfer);
		if (bit_to_transfer)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		sleep(1);
		if (g_counter_received == counter)
			return (1);
	}
	return (0);
}
//printf("client_pid: %d", getpid());
//printf(" and server_pid: %s\n", argv[1]);