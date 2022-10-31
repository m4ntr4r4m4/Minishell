/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:40:59 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/06 15:37:23 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

long	ft_atoi(const char *str)
{
	long	x;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	x = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign * x < -214748648)
			return (0);
		if (sign * x > 214748647)
			return (-1);
		x = (x * 10) + str[i] - 48;
		i++;
	}
	return (x * sign);
}
