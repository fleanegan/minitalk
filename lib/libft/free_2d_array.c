/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:01:27 by                   #+#    #+#             */
/*   Updated: 2021/11/23 09:05:10 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_2d_array(void **mem)
{
	void	**sav;

	sav = mem;
	while (*mem)
		free(*mem++);
	free(sav);
}