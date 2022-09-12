/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:01:26 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/20 16:41:08 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc_char(size_t len)
{
	char	*rtn_ptr;

	rtn_ptr = malloc(((len + 1) * sizeof(char)));
	if (!(rtn_ptr))
		return (NULL);
	return (rtn_ptr);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rtn_ptr;
	size_t	i;

	if (!s || !f)
		return (NULL);
	rtn_ptr = ft_malloc_char(ft_strlen(s));
	i = 0;
	if (!(rtn_ptr))
		return (NULL);
	else
	{
		while (s[i])
		{
			rtn_ptr[i] = f(i, s[i]);
			i++;
		}
		rtn_ptr[i] = '\0';
	}
	return (rtn_ptr);
}
