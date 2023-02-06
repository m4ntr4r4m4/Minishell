/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:41:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/01 16:38:22 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		if (str[i + 1] && str[i] == c && (str[i + 1] != c))
			wc++;
		i++;
	}
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
	j = 0;
	while (j < wc)
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
		len = ft_tr(s, c, quote, &i);
		mots[j] = ft_substr(s, start, len);
		mots[j] = delete_quotes(mots[j]);
		j++;
	}
	mots[j] = 0;
	return (mots);
}


int	check_quotes(char *str)
{
	int	y;

	y = -1;
	while (str[++y])
	{
		if (str[y] == 34)
		{
			y++;
			while (str[y] && str[y] != 34)
				y++;
			if (!str[y])
				return (0);
		}
		else if (str[y] == 39)
		{
			y++;
			while (str[y] && str[y] != 39)
					y++;
			if (!str[y])
				return (0);
		}
		else if (str[y] == 59 || str[y] == 92)
			return (0);
	}
	return (1);
}

int	cpy_str(char **str, int y)
{
	const int	len = ft_strlen(*str);
	char		*newstr;

	newstr = malloc(sizeof(char) * (len + 2));
	if (!newstr)
		return (0);
	newstr[len + 1] = '\0';
	ft_memcpy(newstr, *str, y);
	newstr[y] = ' ';
	ft_memcpy(&newstr[y + 1], &(*str)[y], len - y);
	free(*str);
	*str = newstr;
	return (1);
}

int	add_space(char **str, int *y)
{
	int	vol;

	vol = 0;
	if (token_l((*str)[*y + 1]) != CONTINUE)
	{
		(*y)++;
		vol++;
	}
	if ((*str)[*y])
	{
		(*y)++;
		if (!cpy_str(str, *y - (vol + 1)))
			return (0);
		if (!cpy_str(str, *y + 1))
			return (0);
	}
	return (1);
}

int	parser(char **rd, t_all *all)
{
	char	**str;

	if (check_error(rd, all))
	{
		check_expanser(rd, all);
		str = ft_split_parse(*rd, ' ');
		init_structs(all, str);
		lexer(str, all);
		freetable(str);
		return (1);
	}
	return (0);
}

char	token_l(char token)
{
	if (token == 62)
		return (GREAT);
	else if (token == 60)
		return (LESS);
	else if (token == 124)
		return (PIPE);
	else if (token == 38)
		return (AMPERSAND);
	else
		return (CONTINUE);
}

char	tokens(char *token)
{
	if (!strcmp(token, ">"))
		return (GREAT);
	else if (!strcmp(token, "<"))
		return (LESS);
	else if (!strcmp(token, "<<"))
		return (LESSLESS);
	else if (!strcmp(token, ">>"))
		return (GREATGREAT);
	else if (!strcmp(token, ">&"))
		return (GREATAMPERSAND);
	else if (!strcmp(token, "|"))
		return (PIPE);
	else if (!strcmp(token, "&"))
		return (AMPERSAND);
	else
		return (CONTINUE);
}
