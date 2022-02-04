#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <time.h>

int set_signal_handler(int signal_no, void (*handler_function)(int, siginfo_t *, void *));
void print_signal_message(int signal_no, const siginfo_t *info);

int g_counter_sent = 0;
char	g_message = 0;

void	signal_catcher(int signal_no, siginfo_t *info, void *hmm)
{
	//print_signal_message(signal_no, info);
	(void) signal_no;
	(void) info;
	(void) hmm;
	if (g_counter_sent < 1000)
	{
		kill(info->si_pid, SIGUSR2);
		g_counter_sent++;
	}
	else
	{
		fprintf(stderr, "the server received %d signals\n", g_counter_sent);
		kill(info->si_pid, SIGUSR1);
		kill(getpid(), SIGTERM);
	}
}

void print_signal_message(int signal_no, const siginfo_t *info) {
	ft_putstr_fd("signal_no caught with no: ", 2);
	ft_putnbr_fd(signal_no, 2);
	ft_putstr_fd(", caller pid : ", 2);
	ft_putnbr_fd(info->si_pid, 2);
	ft_putstr_fd("\n", 2);
}

int main (int argc, char** argv)
{
	int	my_pid;

	my_pid = getpid();
	ft_putnbr_fd(my_pid, 1);
	ft_putendl_fd("", 1);
	ft_putnbr_fd(my_pid, 2);
	ft_putendl_fd("", 2);

	if (set_signal_handler(SIGUSR1, signal_catcher))
		return (1);

	while (1)
    {
		pause();
		//ft_putendl_fd("tick", 2);
    }
	//ft_putendl_fd("the server is done and will shutdown now", 2);
	fprintf(stderr, "the server received %d signals\n", g_counter_sent);

    return EXIT_SUCCESS;
	(void) argc;
	(void) argv;
}

