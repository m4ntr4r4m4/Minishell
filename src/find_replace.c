/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:02:42 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 19:54:26 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_replace(const char *s, const char *oldw, int *cnt)
{
	int	i;
	int	oldwlen;

	i = 0;
	oldwlen = strlen(oldw);
	while (s[i] != '\0')
	{
		if (strstr(&s[i], oldw) == &s[i])
		{
			(*cnt)++;
			i += oldwlen - 1;
		}
		i++;
	}
	return (i);
}

char	*replaceword(const char	*s, const char	*oldw, const char *neww)
{
	char	*result;
	int		i;
	int		newwlen;
	int		cnt;
	int		oldwlen;

	cnt = 0;
	newwlen = strlen(neww);
	oldwlen = strlen(oldw);
	i = ft_replace(s, oldw, &cnt);
	result = malloc(sizeof(char) * (i + cnt * (newwlen - oldwlen) + 1));
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
