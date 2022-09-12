/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:59:53 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/26 14:21:09 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i;
	unsigned char	chr;
	unsigned char	*ptr;

	chr = (unsigned char)c;
	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = chr;
		i++;
	}
	return (b);
}
