#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <time.h>

int set_signal_handler(int signal_no, void (*handler_function)(int, siginfo_t *, void *));
int g_counter_received = 0;

void	signal_catcher(int signal_no, siginfo_t *info, void *hmm)
{
	g_counter_received++;
	(void) signal_no;
	(void) info;
	(void) hmm;
	kill(info->si_pid, SIGUSR1);
}

void	suicide(int signal_no, siginfo_t *info, void *hmm)
{
	printf("the client received %d signals\n", g_counter_received);
	(void) signal_no;
	(void) info;
	(void) hmm;
	kill(getpid(), SIGTERM);
}

int main (int argc, char** argv)
{
	int	server_id;

	printf("client_pid: %d", getpid());
	printf(" and server_pid: %s\n", argv[1]);
	server_id = ft_atoi(argv[1]);
	if (set_signal_handler(SIGUSR2, signal_catcher), \
		set_signal_handler(SIGUSR1, suicide))
		return (1);
	kill(server_id, SIGUSR1);
	int test = 0;
	while (1)
	{
		test = g_counter_received;
		sleep(1);
		if (g_counter_received == test)
			ft_putendl_fd("tick", 2);
	}
	printf("the client received %d signals\n", g_counter_received);
    return EXIT_SUCCESS;
	(void) argc;
	(void) argv;
	(void) server_id;
}