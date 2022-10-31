/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:19:43 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/12 21:00:21 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*count;

	count = lst;
	i = 0;
	while (count != NULL)
	{
		count = count->next;
		i++;
	}
	return (i);
}
