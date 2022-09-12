/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:55:55 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/27 10:46:09 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_sizer(const char *ptn)
{
	char	*str;
	size_t	i;

	str = (char *)ptn;
	i = 0;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
		i++;
	return (i);
}

static char	*ft_trim_sign(const char *str)
{
	char	*ptn;

	ptn = (char *)str;
	if (ptn[0] == '-' || ptn[0] == '+')
		ptn++;
	return (ptn);
}

static unsigned long long	ft_calc_res(const char *ptn)
{
	unsigned long long	res;
	char				*str;

	str = (char *)ptn;
	res = 0;
	while (str[0])
	{
		if (str[0] >= '0' && str[0] <= '9')
			res = (res * 10) + (str[0] - '0');
		else
			break ;
		str++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	char				*ptn;
	unsigned long long	res;
	int					sign;

	ptn = (char *)str;
	sign = 1;
	while (ptn[0] && (ptn[0] == ' ' || (ptn[0] >= 9 && ptn[0] <= 13)))
		ptn++;
	if (ptn[0] == '-')
		sign = -1;
	ptn = ft_trim_sign(ptn);
	if (ft_sizer(ptn) > 19 && sign == 1)
		return (-1);
	if (ft_sizer(ptn) > 19 && sign == (-1))
		return (0);
	res = ft_calc_res(ptn);
	if (res >= 9223372036854775808ULL && sign == 1)
		return (-1);
	if (res >= 9223372036854775808ULL && sign == (-1))
		return (0);
	return (sign * res);
}
