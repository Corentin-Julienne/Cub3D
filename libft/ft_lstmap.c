/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:36:41 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/12 15:58:27 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list_starter;
	t_list	*new_elem;

	if (!lst || !f)
		return (NULL);
	list_starter = NULL;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (!new_elem)
		{
			ft_lstclear(&list_starter, del);
			return (NULL);
		}
		ft_lstadd_back(&list_starter, new_elem);
		lst = lst->next;
	}
	return (list_starter);
}
