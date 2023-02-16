/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:02:42 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 18:31:56 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_replace(const char *s, const char *oldw)
{
	int	i;
	int	cnt;
	int	oldwlen;

	i = 0;
	oldwlen = strlen(oldw);
	cnt = 0;
	while (s[i] != '\0')
	{
		if (strstr(&s[i], oldw) == &s[i])
		{
			cnt++;
			i += oldwlen - 1;
		}
		i++;
	}
	return (i + cnt);
}

char	*replaceword(const char	*s, const char	*oldw, const char *neww)
{
	char	*result;
	int		i;
	int		newwlen;
	int		oldwlen;

	newwlen = strlen(neww);
	oldwlen = strlen(oldw);
	i = ft_replace(s, oldw);
	result = malloc(sizeof(char) * (i * (newwlen - oldwlen) + 1));
	i = 0;
	while (*s)
	{
		if (strstr(s, oldw) == s)
		{
			strcpy(&result[i], neww);
			i += newwlen;
			s += oldwlen;
		}
		else
			result[i++] = *s++;
	}
	result[i] = '\0';
	return (result);
}
