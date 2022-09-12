/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:59:11 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/20 17:59:36 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	size_t					stopper;
	int						dif;
	unsigned char			*ptr_s1;
	unsigned char			*ptr_s2;

	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	i = 0;
	dif = 0;
	stopper = 0;
	while (i < n && stopper == 0)
	{
		if (ptr_s1[i] != ptr_s2[i])
		{
			dif = ptr_s1[i] - ptr_s2[i];
			stopper++;
		}
		i++;
	}
	return (dif);
}
