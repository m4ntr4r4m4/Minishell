/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:47:23 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/07 17:00:09 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_delete(char *str, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	if (str[i] != c && str[i] != '\0')
		wc++;
	while (str[i])
	{
		if (str[i] == '"')
		{
			str[i] = c;
		}
		if (str[i + 1] && str[i] == c && (str[i + 1] != c))
			wc++;
		i++;
	}
	return (wc);
}

static	int	ft_tr_delete(const char *s, int c, int *quote, int *i)
{
	int	len;

	len = 0;
	while (((s[*i] != c || (*quote % 2) != 0) && s[*i] != '\0'))
	{
		(*i)++;
		if (s[*i] == '"')
			*quote+=1;
		len++;
	}
	return (len);
}

static char *delete_quotes_delete(char *str)
{
	int	i;
	int	count;
	char	*new;
	int	x;

	count = 0;
	i = -1;
	while(str[++i])
	{
		if (str[i] != '"')
			count++;
	}
	new = malloc(count + 1);
	i = -1;
	x = 0;
	new[count] = '\0';
	while (str[++i])
	{
		if (str[i] != '"')
			new[x++] = str[i];
	}
	return new;
}


static char	**cpy_delete(char **mots, char const *s, int wc, char c)
{
	int			i;
	int			j;
	int			len;
	int			start;
	static int	quote;

	i = 0;
	j = 0;
	while (j < wc)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '"')
		{
			quote++;
			i++;
		}
		start = i;
		len = ft_tr_delete(s, c, &quote, &i);
		mots[j] = ft_substr(s, start, len);
		j++;
	}
	mots[j] = 0;
	return (mots);
}

char	**ft_split_delete(char const *s, char c)
{
	char	**mots;
	int		wc;

	if (!s)
		return (NULL);
	wc = word_delete((char *)s, c);
	mots = malloc(sizeof(char *) * (wc + 1));
	if (!mots)
		return (0);
	mots = cpy_delete(mots, s, wc, c);
	return (mots);
}
