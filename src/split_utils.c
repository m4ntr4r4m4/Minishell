/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:02:11 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 18:02:12 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_iterate(char *str, int *i, char c, int *wc)
{
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"')
			(*i)++;
	}
	if (str[*i] == 39)
	{
		(*i)++;
		while (str[*i] != 39)
			(*i)++;
	}
	if (str[*i + 1] && str[*i] == c && (str[*i + 1] != c))
		(*wc)++;
	(*i)++;
}

int	word(char *str, char c)
{
	int	i;
	int	wc;
	int	quote;

	i = 0;
	quote = 0;
	wc = 0;
	if (str[i] != c && str[i] != '\0')
		wc++;
	while (str[i])
		word_iterate(str, &i, c, &wc);
	return (wc);
}

char	**cpy(char **mots, char *s, int wc, char c)
{
	int			i;
	int			j;
	int			len;
	int			start;
	char		quote;

	i = 0;
	j = -1;
	while (++j < wc)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '"')
			quote = '"';
		else if (s[i] == 39)
			quote = 39;
		else
			quote = ' ';
		start = i;
		len = ft_tr(s, quote, &i);
		mots[j] = ft_substr(s, start, len);
		mots[j] = delete_quotes(mots[j]);
	}
	mots[j] = 0;
	return (mots);
}
