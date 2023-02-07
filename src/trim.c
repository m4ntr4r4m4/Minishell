/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:32:41 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/07 15:00:37 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrimtail(char const *s1, char const *set)
{
	size_t	e;
	char	*str1;

	if (!s1)
		return (NULL);
	e = ft_strlen((char *)s1);
	if (e == ft_strlen((char *)set) && !ft_strncmp((char *)set, (char *)s1, e))
		return (ft_strdup(""));
	if (e)
		while (ft_strchr(set, s1[e - 1]) != 0)
			e--;
	str1 = malloc(sizeof(char) * e + 1);
	if (!str1)
		return (NULL);
	ft_strlcpy(str1, (char *)s1, e + 1);
	return (str1);
}
