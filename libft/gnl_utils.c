/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:16:33 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 13:16:51 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_mallocable(char *patch)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	if (!patch[i])
		return (NULL);
	while (patch[i] && patch[i] != '\n')
		i++;
	if (patch[i] == '\n')
		str = malloc(sizeof(char) * (i + 2));
	else if (patch[i] == '\0')
		str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	return (str);
}
