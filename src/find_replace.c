/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_replace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:02:42 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/15 22:32:31 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replaceWord(const char* s, const char* oldW, const char* newW)
{
	char	*result;
	int		i;
	int		cnt;
	int		newWlen;
	int		oldWlen;

	newWlen = strlen(newW); 
	oldWlen = strlen(oldW); 
    cnt = 0; 
	i = 0;
	while (s[i] != '\0')
	{
        if (strstr(&s[i], oldW) == &s[i])
		{
			cnt++;
			i += oldWlen - 1;
		}
		i++;
	}
    result = malloc(sizeof(char) * ( i + cnt * (newWlen - oldWlen) + 1));
    i = 0;
    while (*s)
	{
		if (strstr(s, oldW) == s)
		{
			strcpy(&result[i], newW);
			i += newWlen;
			s += oldWlen;
		}
		else
			result[i++] = *s++;
	}
	result[i] = '\0';
	return result;
}
