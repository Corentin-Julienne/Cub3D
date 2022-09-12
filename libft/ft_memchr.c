/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:59:04 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/20 17:57:53 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptn_finder;
	unsigned char	*ptn_s;
	unsigned char	us_c;
	unsigned long	i;

	us_c = (unsigned char)c;
	ptn_s = (unsigned char *)s;
	ptn_finder = NULL;
	i = 0;
	while (i < n)
	{
		if (ptn_s[i] == us_c)
		{
			ptn_finder = ptn_s + i;
			return ((void *)ptn_finder);
		}
		i++;
	}
	return ((void *)ptn_finder);
}
