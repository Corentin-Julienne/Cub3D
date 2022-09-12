/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:58:49 by cjulienn          #+#    #+#             */
/*   Updated: 2021/07/16 16:03:02 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	ft_llint_sizer(long long n)
{
	long long	size;

	size = 1;
	if (n < 0)
	{
		size++;
		n = (n * (-1));
	}
	while (n >= 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static long long	ft_power(long long len_integer, long long i)
{
	long long	multiplicator;

	multiplicator = 1;
	len_integer = len_integer - i;
	while (len_integer > 1)
	{
		multiplicator = multiplicator * 10;
		len_integer--;
	}
	return (multiplicator);
}

static char	*ft_string_fulfiller(char *str, long long n, long long len)
{
	long long	i;
	long long	multiplicator;

	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		n = n * (-1);
		i++;
	}
	str[len] = '\0';
	multiplicator = ft_power(len, i);
	while (len > i)
	{
		str[i] = ((n / multiplicator) + '0');
		n = n % multiplicator;
		multiplicator = (multiplicator / 10);
		i++;
	}
	return (str);
}

char	*ft_lltoa(long long n)
{
	char			*int_string;
	long long int	len_integer;

	len_integer = ft_llint_sizer(n);
	int_string = malloc((len_integer + 1) * (sizeof(char)));
	if (!(int_string))
		return (NULL);
	int_string = ft_string_fulfiller(int_string, n, len_integer);
	return (int_string);
}
