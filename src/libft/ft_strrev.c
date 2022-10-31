/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:19:30 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/15 12:21:13 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	swp;

	i = 0;
	len = 0;
	while (str[len] != '\0')
		++len;
	--len;
	while (i <= len)
	{
		swp = str[len];
		str[len] = str[i];
		str[i] = swp;
		--len;
		++i;
	}
	return (str);
}
