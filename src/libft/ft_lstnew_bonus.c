/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:52:15 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/13 14:37:28 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}
