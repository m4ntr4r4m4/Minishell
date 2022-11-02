/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 21:11:31 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/12 21:22:46 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*new;

	if (!lst)
		return (0);
	new = lst;
	while (new->next != NULL)
		new = new->next;
	return (new);
}
