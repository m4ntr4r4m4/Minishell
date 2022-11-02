/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 15:29:43 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/05 21:20:32 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	x;
	unsigned int	z;
	unsigned int	y;

	i = 0;
	x = (unsigned int)ft_strlen(dest);
	y = (unsigned int)ft_strlen(src);
	z = x;
	if (size < (x + 1))
		return (y + size);
	else
	{	
		while (src[i] && i < (size - z - 1))
		{
			dest[x] = src[i];
			x++;
			i++;
		}
		dest[x] = '\0';
		return (z + y);
	}
}
