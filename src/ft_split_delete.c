/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <ahammoud@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:47:23 by ahammoud          #+#    #+#             */
/*   Updated: 2023/03/04 13:28:50 by ahammoud         ###   ########.fr       */
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
		if (str[i + 1] && str[i] == c && (str[i + 1] != c))
			wc++;
		if (str[i + 1] && str[i] == '$' && i > 1 && (str[i - 1] != c))
			wc++;
		if (i > 1 && (str[i] == 39 || str[i] == '"'))
			wc++;
		i++;
	}
	return (wc);
}

static	int	ft_tr_delete(const char *s, int c, int *quote, int *i)
{
	int	len;

	len = 0;
	while (((s[*i] != c) && s[*i] != '\0'))
	{
		(*i)++;
		if (s[*i] == '"')
			*quote += 1;
		len++;
		if (s[*i] == '$')
			break ;
		if (s[*i] == 39 || s[*i] == '"')
			break ;
	}
	return (len);
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
