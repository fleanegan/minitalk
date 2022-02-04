#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <time.h>

int set_signal_handler(int signal_no, void (*handler_function)(int, siginfo_t *, void *));
int	g_message = 1;

int	is_byte_finished()
{
	if (g_message & 0b10000000)
	{
		fprintf(stderr, "received char %c, ascii value %d\n", g_message & 0b01111111, g_message & 0b01111111);
		return (1);
	}
	return (0);
}

void	handle_incomming_bit(int signal_no, int caller_pid)
{
	g_message = g_message << 1;
	if (signal_no == SIGUSR2)
		g_message = g_message | 1;
	if (! is_byte_finished())
		kill(caller_pid, SIGUSR2);
	else
	{
		g_message = 1;
		//kill(caller_pid, SIGUSR1);
		//kill(getpid(), SIGTERM);
	}
}

void	receive_zero_bit(int signal_no, siginfo_t *info, void *hmm)
{
	(void) signal_no;
	(void) hmm;
	handle_incomming_bit(SIGUSR1, info->si_pid);
}

void	receive_one_bit(int signal_no, siginfo_t *info, void *hmm)
{
	(void) signal_no;
	(void) hmm;
	handle_incomming_bit(SIGUSR2, info->si_pid);
}

int main (int argc, char** argv)
{
	int	my_pid;

	my_pid = getpid();
	ft_putnbr_fd(my_pid, 1);
	ft_putendl_fd("", 1);
	ft_putnbr_fd(my_pid, 2);
	ft_putendl_fd("", 2);

	if (set_signal_handler(SIGUSR1, receive_zero_bit) \
		|| set_signal_handler(SIGUSR2, receive_one_bit))
		return (1);

	while (1)
    {
		pause();
		//ft_putendl_fd("tick", 2);
    }
	//ft_putendl_fd("the server is done and will shutdown now", 2);

    return EXIT_SUCCESS;
	(void) argc;
	(void) argv;
}

