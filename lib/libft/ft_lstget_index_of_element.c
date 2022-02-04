/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_index_of_element.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:04 by                   #+#    #+#             */
/*   Updated: 2021/12/14 13:18:46 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstget_index_of_element(t_list *lst, t_list *element)
{
	int	index;

	if (! lst)
		return (-1);
	index = 0;
	while (lst)
	{
		if (lst == element)
			return (index);
		index++;
		lst = lst->next;
	}
	return (-1);
}
