/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:02:18 by                   #+#    #+#             */
/*   Updated: 2021/12/14 13:18:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*memory_ptr;

	memory_ptr = (unsigned char *) s;
	while (n--)
	{
		*memory_ptr = c;
		memory_ptr++;
	}
	return (s);
}
