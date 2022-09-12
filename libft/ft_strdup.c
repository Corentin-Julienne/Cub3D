/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:00:53 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/27 09:58:20 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char				*copy;
	unsigned long		sizer;

	sizer = ft_strlen(s1) + 1;
	copy = malloc(sizer * (sizeof(char)));
	if (!(copy))
		return (NULL);
	ft_strcpy(copy, s1);
	return (copy);
}
