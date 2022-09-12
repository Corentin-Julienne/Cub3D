/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:35:43 by cjulienn          #+#    #+#             */
/*   Updated: 2021/08/06 15:27:29 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_base_converter(unsigned long nb, char *base, unsigned long b_s)
{
	if (nb >= b_s)
	{
		ft_base_converter((nb / b_s), base, b_s);
		ft_putchar_fd(base[(nb % b_s)], 1);
	}
	else
		ft_putchar_fd(base[nb], 1);
}

void	ft_putlnbr_base(unsigned long nb, char *base)
{
	unsigned long		base_size;

	base_size = 0;
	while (base[base_size] != '\0')
		base_size++;
	ft_base_converter(nb, base, base_size);
}
