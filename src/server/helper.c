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

#include "libft.h"
#include <signal.h>

void	finalize_message(int *byte)
{
	*byte = *byte & 0b01111111;
}

int	is_byte_finished(const int *byte)
{
	return (*byte & 256);
}

void	apply_sent_bit_to_message(int signal_no, t_list *message, int **byte)
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
