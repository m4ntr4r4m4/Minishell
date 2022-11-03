/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:22:19 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/03 16:58:14 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_table(char **tab, int fd)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] != 0)
	{
		ft_putstr_fd("TABLE:", fd);
		ft_putstr_fd(tab[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}
