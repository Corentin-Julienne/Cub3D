/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:01:43 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/21 10:01:27 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*ptn;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	ptn = (char *)haystack;
	if (needle[0] == '\0')
		return (ptn);
	while (ptn[i] && i < len)
	{
		if (ptn[i] == needle[j])
		{
			while (ptn[i + j] == needle[j] && (i + j) < len)
			{
				if (needle[j + 1] == '\0')
					return (ptn + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
