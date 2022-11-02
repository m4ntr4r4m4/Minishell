/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 21:33:15 by ahammoud          #+#    #+#             */
/*   Updated: 2022/02/25 19:55:07 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s;
	size_t	e;
	char	*str1;

	if (!s1)
		return (NULL);
	s = 0;
	while (s1[s] && ft_strchr(set, s1[s]))
		s++;
	e = ft_strlen((char *)s1 + s);
	if (e)
		while (ft_strchr(set, s1[s + e - 1]) != 0)
			e--;
	str1 = malloc(sizeof(char) * e + 1);
	if (!str1)
		return (NULL);
	(void)ft_strlcpy(str1, (char *)&s1[s], e + 1);
	return (str1);
}
