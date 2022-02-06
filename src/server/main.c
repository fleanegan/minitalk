

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libft_auxilliar.h>
#include <time.h>

int	set_signal_handler(int signal_no, \
	void (*handler_function)(int, siginfo_t *, void *));
t_list	*g_message;

int	is_byte_finished(void)
{
	int	*byte;

	byte = ft_lstlast(g_message)->content;
	if (*byte & 256)
	{
		*byte = *byte & 0b01111111;
		return (1);
	}
	return (0);
}

void	clean_up_for_next_message(t_list *message)
{
	char	*result;

	result = char_list_to_char_array(message);
	ft_putendl_fd(result, 2);
	free(result);
	ft_lstclear(&g_message, free);
}

void	prepare_next_bit(const siginfo_t *info)
{
	ft_lstadd_back(&g_message, ft_lstnew(malloc_int(1)));
	if (!ft_lstlast(g_message) || ! ft_lstlast(g_message)->content)
	{
		ft_lstclear(&g_message, free);
		kill(info->si_pid, SIGUSR1);
		exit(1);
	}
}

void	handle_incomming_bit(int signal_no, siginfo_t *info, void *hmm)
{
	int	*byte;

	byte = ft_lstlast(g_message)->content;
	*byte = *byte << 1;
	if (signal_no == SIGUSR2)
		*byte = *byte | 1;
	if (! is_byte_finished())
		kill(info->si_pid, SIGUSR2);
	else
	{
		if (! *byte)
			clean_up_for_next_message(g_message);
		prepare_next_bit(info);
		kill(info->si_pid, SIGUSR2);
	}
	(void) hmm;
}

int	main(void)
{
	int	my_pid;

	my_pid = getpid();
	ft_putnbr_fd(my_pid, 1);
	ft_putendl_fd("", 1);
	g_message = ft_lstnew(malloc_int(1));
	if (! g_message || ! g_message->content)
	{
		if (! g_message->content)
			free(g_message);
		return (1);
	}
	if (set_signal_handler(SIGUSR1, handle_incomming_bit) \
		|| set_signal_handler(SIGUSR2, handle_incomming_bit))
	{
		ft_lstclear(&g_message, free);
		return (1);
	}
	while (1)
		pause();
}
