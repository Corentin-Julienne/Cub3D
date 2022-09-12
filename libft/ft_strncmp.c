/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:01:36 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/21 09:59:50 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	iter;

	iter = 0;
	if (n == 0)
		return (0);
	while (iter < n - 1 && s1[iter] && s2[iter] && s1[iter] == s2[iter])
		iter++;
	return ((unsigned char)s1[iter] - (unsigned char)s2[iter]);
}
