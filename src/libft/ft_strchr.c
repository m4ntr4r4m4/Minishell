/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:28:58 by ahammoud          #+#    #+#             */
/*   Updated: 2022/02/25 19:57:35 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const	char *s, int c)
{
	int		i;
	int		j;

	j = -1;
	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == c)
			j = i;
		i--;
	}
	if (j == -1)
		return (NULL);
	return ((char *)&s[j]);
}
