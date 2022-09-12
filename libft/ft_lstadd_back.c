/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:36:27 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/12 14:23:36 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{	
	t_list	*last_elem;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	if (alst && new)
	{
		last_elem = ft_lstlast(*alst);
		last_elem->next = new;
	}
}
