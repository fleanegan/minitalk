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
#include <libft_auxilliar.h>

t_list	*g_message = NULL;

int				set_signal_handler(int signal_no, \
				void (*handler_function)(int, siginfo_t *, void *));
unsigned long	is_byte_finished(const unsigned long *byte);
void			print_and_free_list(t_list **message);
void			apply_sent_bit_to_message( \
				int signal_no, t_list *message, unsigned long **byte);
void			finalize_character(unsigned long *byte);
unsigned long	*append_bit_to_message(const int signal_no, \
				unsigned long **byte, t_list **message, const int client_pid);
void			prepare_next_byte(t_list **message, const int client_pid);

void	handle_incomming_bit(int signal_no, siginfo_t *info, void *hmm)
{
	unsigned long	*character;

	character = append_bit_to_message(\
				signal_no, &character, &g_message, info->si_pid);
	if (! is_byte_finished(character))
		kill(info->si_pid, SIGUSR2);
	else
	{
		finalize_character(character);
		if (*character == 0)
			print_and_free_list(&g_message);
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
	if (set_signal_handler(SIGUSR1, handle_incomming_bit) \
		|| set_signal_handler(SIGUSR2, handle_incomming_bit))
		return (1);
	while (1)
		pause();
}

unsigned long	*append_bit_to_message(const int signal_no, \
				unsigned long **byte, t_list **message, const int client_pid)
{
	if (! *message)
		prepare_next_byte(message, client_pid);
	ft_putendl_fd("before apply", 2);
	apply_sent_bit_to_message(signal_no, *message, byte);
	ft_putendl_fd("after apply", 2);
	if (is_byte_finished((*byte)))
		prepare_next_byte(message, client_pid);
	return (*byte);
}
