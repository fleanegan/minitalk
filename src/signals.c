#include <signal.h>
#include <stdlib.h>
#include <string.h>

int set_signal_handler(int signal_no, void (*handler_function)(int, siginfo_t *, void *))
{
	struct sigaction	act;

	memset(&act, 0, sizeof act);
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_sigaction = handler_function;
	act.sa_flags = SA_SIGINFO;
	return (sigaction(signal_no,  &act, NULL));
}
