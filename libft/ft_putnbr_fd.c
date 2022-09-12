/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:00:14 by cjulienn          #+#    #+#             */
/*   Updated: 2021/04/20 17:50:55 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int	long_n;

	long_n = n;
	if (long_n < 0)
	{
		ft_putchar_fd('-', fd);
		long_n = long_n * (-1);
	}
	if (long_n >= 10)
	{
		ft_putnbr_fd((long_n / 10), fd);
		ft_putchar_fd(((long_n % 10) + '0'), fd);
	}
	else if (long_n < 10)
		ft_putchar_fd((long_n + '0'), fd);
}
