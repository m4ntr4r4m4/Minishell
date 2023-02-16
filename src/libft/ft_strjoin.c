/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 01:30:36 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 16:34:42 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (0);
		s1 = "";
	}
	dest = NULL;
	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	if (j != 0 || i != 0 || (char)s1[i] == '\0' || (char)s2[i] == '\0')
	{
		dest = malloc((j + i + 1) * sizeof(char));
		if (!dest)
			return (NULL);
		ft_memcpy(dest, s1, i);
		ft_memcpy(&dest[i], s2, j);
		dest[i + j] = '\0';
	}
	return (dest);
}
