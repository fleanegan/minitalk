/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c								            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:49 by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:11:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_auxilliar.h"
#include <signal.h>

#define BYTES_IN_CHAR 4

void	finalize_character(unsigned long *byte)
{
	*byte = *byte & (((1l << (8 * BYTES_IN_CHAR))) - 1);
}

unsigned long	is_byte_finished(const unsigned long *byte)
{
	return (*byte & ((1l << (8 * BYTES_IN_CHAR))));
}

void	apply_sent_bit_to_message( \
		int signal_no, t_list *message, unsigned long **byte)
{
	*byte = ft_lstlast(message)->content;
	**byte = **byte << 1;
	if (signal_no == SIGUSR2)
		**byte = **byte | 1;
}

void	print_and_free_list(t_list **message)
{
	t_list	*lst;

	lst = *message;
	while (lst)
	{
		ft_putchar_fd(*(char *)lst->content, 2);
		lst = lst->next;
	}
	ft_putstr_fd("\n", 2);
	ft_lstclear(message, free);
}

void	prepare_next_byte(t_list **message, const int client_pid)
{
	t_list	*new_byte;

	new_byte = ft_lstnew(malloc_unsigned_long(1));
	if (! new_byte || ! new_byte->content)
	{
		ft_lstclear(message, free);
		kill(client_pid, SIGUSR1);
		exit(1);
	}
	ft_lstadd_back(message, new_byte);
}
