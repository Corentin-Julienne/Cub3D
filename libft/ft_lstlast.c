/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:36:38 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/12 12:23:07 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	size_t	size;

	if (!lst)
		return (lst);
	size = ft_lstsize(lst);
	while (size - 1 > 0)
	{
		lst = lst->next;
		size--;
	}
	return (lst);
}
