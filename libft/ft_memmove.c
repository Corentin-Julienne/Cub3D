/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:59:48 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/27 09:56:04 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*ptr_dst;
	unsigned char			*ptr_src;

	ptr_dst = (unsigned char *)dst;
	ptr_src = (unsigned char *)src;
	if (ptr_dst == ptr_src)
		return (ptr_src);
	if (ptr_src < ptr_dst)
	{
		while (len > 0)
		{
			ptr_dst[len - 1] = ptr_src[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(ptr_dst, ptr_src, len);
	return (dst);
}
