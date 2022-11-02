/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:25:29 by ahammoud          #+#    #+#             */
/*   Updated: 2022/02/25 20:01:05 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	memory(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	calc(char *total, int var, long num)
{
	int	i;

	i = 0;
	while (var - 1 >= i)
	{
		if (num < 0)
		{
			total[i++] = '-';
			num = -num;
		}
		while (num > 0)
		{
			total[var-- - 1] = ((num % 10) + 48);
			num /= 10;
		}
	}
}

char	*ft_itoa(int n)
{
	long	num;
	char	*total;
	int		var;

	num = n;
	var = memory(num);
	total = malloc(sizeof(char) * (var + 1));
	if (!total)
		return (NULL);
	total[var] = '\0';
	if (num != 0)
		calc(total, var, num);
	else
		total[0] = '0';
	return (total);
}
