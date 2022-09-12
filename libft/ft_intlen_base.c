/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:37:50 by cjulienn          #+#    #+#             */
/*   Updated: 2021/07/23 13:37:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen_base(unsigned long long num, size_t base)
{
	size_t	res;

	res = 0;
	if (num == 0)
	{
		res = 1;
		return (res);
	}
	while (num > 0)
	{
		res++;
		num = num / base;
	}
	return (res);
}
