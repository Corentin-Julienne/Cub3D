/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:00:14 by cjulienn          #+#    #+#             */
/*   Updated: 2021/07/16 15:45:25 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlnbr_fd(long long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * (-1);
	}
	if (n >= 10)
	{
		ft_putlnbr_fd((n / 10), fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
	else if (n < 10)
		ft_putchar_fd((n + '0'), fd);
}
