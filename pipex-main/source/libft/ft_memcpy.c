/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:53:04 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/15 17:09:44 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest1;
	const char	*src1;

	if (!src && !dst)
		return (NULL);
	dest1 = dst;
	src1 = src;
	i = 0;
	while (i < n && (dest1[i] || src1[i]))
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest1);
}
