/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c									            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:49 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <libft_auxilliar.h>

t_list	*g_message;

int		set_signal_handler(int signal_no, \
		void (*handler_function)(int, siginfo_t *, void *));
int		is_byte_finished(const int *byte);
void	print_and_free_list(t_list **message);
void	apply_sent_bit_to_message(int signal_no, t_list *message, int **byte);
void	finalize_message(int *byte);

void	handle_shutdown(int signal_no, siginfo_t *info, void *hmm)
{
	if (signal_no == SIGTERM)
		ft_lstclear(&g_message, free);
	exit(0);
	(void) hmm;
	(void) info;
}

void	prepare_next_byte(const siginfo_t *info)
{
	t_list	*new_byte;

	new_byte = ft_lstnew(malloc_int(1));
	if (! new_byte || ! new_byte->content)
	{
		ft_lstclear(&g_message, free);
		kill(info->si_pid, SIGUSR1);
		exit(1);
	}
	ft_lstadd_back(&g_message, new_byte);
}

void	handle_incomming_bit(int signal_no, siginfo_t *info, void *hmm)
{
	int	*byte;

	apply_sent_bit_to_message(signal_no, g_message, &byte);
	if (! is_byte_finished(byte))
		kill(info->si_pid, SIGUSR2);
	else
	{
		finalize_message(byte);
		if (! *byte)
			print_and_free_list(&g_message);
		prepare_next_byte(info);
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
		|| set_signal_handler(SIGUSR2, handle_incomming_bit) \
		|| set_signal_handler(SIGTERM, handle_shutdown))
	{
		ft_lstclear(&g_message, free);
		return (1);
	}
	while (1)
		pause();
}
