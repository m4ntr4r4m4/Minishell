/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:39:19 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/13 15:09:07 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(char **rd)
{
	if (!check_tokens(*rd))
		return (0);
	if (!check_spaces(rd))
		return (0);
	if (!check_quotes(*rd))
		return (0);
	return (1);
}

int	check_spaces(char **temp)
{
	int		y;
	char	token;
	char	*str;

	str = *temp;
	y = -1;
	while (str[++y] != '\0')
	{
		token = token_l(str[y]);
		if (token != CONTINUE)
		{
			if (!add_space(&str, &y))
				return (0);
			if (str[y] == '\0')
				return (1);
		}
	}
	*temp = str;
	return (1);
}

void	check_expanser(char **str, t_all *all)
{
	int		i;
	char	*rd;

	rd = *str;
	i = -1;
	while (rd[++i] != '\0')
	{
		if (rd[i] == 39)
		{
			i++;
			while (rd[i] != 39)
				i++;
		}
		if (rd[i] == '$')
		{
			expander(str, all);
			rd = *str;
			break ;
		}
	}
}

int	check_token(char token, char prev, char str, int count)
{
	if (prev != CONTINUE)
	{
		if (token != prev || str != CONTINUE)
		{
			if (prev == LESS && token == GREAT)
				return (1);
			return (0);
		}
	}
	else if (!count)
		return (0);
	return (1);
}

int	check_tokens(char *str)
{
	int		i;
	char	token;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		token = token_l(str[i]);
		if (token != CONTINUE)
		{
			if (!check_token(token, token_l(str[i - 1]),
					token_l(str[i + 1]), count))
				return (0);
			count = 0;
		}
		else if (str[i] != 32)
			count = 1;
	}
	if (!count)
		return (0);
	return (1);
}
