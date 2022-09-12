/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:02:28 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/21 10:11:17 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*ptn;
	char			d;

	ptn = (char *)s;
	i = ft_strlen(s);
	d = (char)c;
	while (i >= 0)
	{
		if (ptn[i] == d)
			return (ptn + i);
		i--;
	}
	return (NULL);
}
