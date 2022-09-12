/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:57:29 by cjulienn          #+#    #+#             */
/*   Updated: 2021/04/29 13:17:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr_calloc;

	if (count == 0 || size == 0)
	{
		size = 1;
		count = 1;
	}
	ptr_calloc = malloc(count * size);
	if (!(ptr_calloc))
		return (NULL);
	ft_bzero(ptr_calloc, (count * size));
	return (ptr_calloc);
}
