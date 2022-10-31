/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:38:57 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/15 17:26:08 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		l;
	char	*dup;

	i = 0;
	l = ft_strlen(src) + 1;
	dup = malloc(l * sizeof(char));
	if (!dup)
		return (0);
	ft_strcpy(dup, src);
	return (dup);
}
