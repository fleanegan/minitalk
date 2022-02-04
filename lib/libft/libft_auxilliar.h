/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_auxilliar.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <fschlute>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:03:02 by                   #+#    #+#             */
/*   Updated: 2021/12/03 11:32:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_AUXILLIAR_H
# define LIBFT_AUXILLIAR_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

size_t	count_leading_trimmable(const char *src, const char *set);
size_t	count_trailing_trimmable(const char *src, const char *set);
size_t	calc_len_sub_str(const char *src, const char *set);
int		count_substrings(const char *s, char *c);
int		is_char_in_set(char in, const char *set);
int		calc_digits_in_number(int in);
size_t	calc_min_unsigned(size_t a, size_t b);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	ft_lstput_nbr_bonus(t_list *lst);
void	ft_lstput_char_bonus(t_list *lst);
void	ft_lstput_str_bonus(t_list *lst);
#endif
