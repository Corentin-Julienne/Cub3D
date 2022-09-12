/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:02:36 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/10 16:31:20 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_trimbfr(char *str, char const *set, size_t set_size)
{
	size_t	i;

	i = 0;
	while (str[0] && i <= set_size)
	{
		if (str[0] == set[i])
		{
			str++;
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

static size_t	ft_count_trimmed_char(char const *str, char const *set)
{
	size_t		res;
	long long	index;
	long long	j;
	long long	error;

	res = 0;
	j = 0;
	error = 0;
	index = ft_strlen(str) - 1;
	while (index >= 0 && error == 0)
	{
		if (str[index] == set[j])
		{
			res++;
			index--;
			j = 0;
		}
		else if (set[j])
			j++;
		else
		{
			error++;
		}
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			trimmed_size;
	size_t			i;
	char			*trm_str;
	char			*str;

	if (!s1 || !set)
		return (NULL);
	str = (char *)s1;
	str = ft_trimbfr(str, set, ft_strlen(set));
	trimmed_size = ft_count_trimmed_char(str, set);
	trm_str = (malloc((ft_strlen(str) + 1 - trimmed_size) * sizeof(char)));
	if (!(trm_str))
		return (NULL);
	i = 0;
	while (i < (ft_strlen(str) - trimmed_size))
	{
		trm_str[i] = str[i];
		i++;
	}
	trm_str[i] = '\0';
	return (trm_str);
}
