/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:32:27 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/15 16:45:58 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*aux;

	if (!lst || !f)
		return (0);
	aux = 0;
	new = 0;
	while (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (!aux)
			ft_lstclear(&aux, del);
		ft_lstadd_back(&new, aux);
		lst = lst->next;
	}
	return (new);
}
