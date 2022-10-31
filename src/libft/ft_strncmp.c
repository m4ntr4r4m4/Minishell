/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 10:08:55 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/11 17:32:11 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((str1[i] != '\0' && str2[i] != '\0'\
				) && (i < n - 1 && str1[i] == str2[i]))
		i++;
	if (s1[i] == '\200' && s2[i] == '\0')
		return (1);
	return (str1[i] - str2[i]);
}
