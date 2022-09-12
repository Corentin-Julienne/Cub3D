/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:58:57 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/26 14:19:52 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned long	i;
	unsigned char	d;
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;
	unsigned char	*ptr_return;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	ptr_return = NULL;
	i = 0;
	d = (unsigned char)c;
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		if (ptr_src[i] == d)
		{
			ptr_return = ptr_dst + i + 1;
			return (ptr_return);
		}
		i++;
	}
	return (ptr_return);
}
