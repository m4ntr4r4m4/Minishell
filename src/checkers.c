/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:39:19 by ahammoud          #+#    #+#             */
/*   Updated: 2023/03/08 15:01:00 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(char **rd)
{
	if (!check_tokens(*rd))
		return (0);
	if (!check_quotes(*rd))
		return (0);
	if (!check_spaces(rd))
		return (0);
	return (1);
}

int	s_quotes(char *str, int y)
{
	if (str[y] == '"')
	{
		y++;
		while (str[y] != '"')
			y++;
	}
	if (str[y] == 39)
	{
		y++;
		while (str[y] != 39)
			y++;
	}
	return (y);
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
		y = s_quotes(str, y);
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

void	check_exp_utils(char **rd, char **str, t_all *all)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while ((*rd)[++i] != '\0')
	{
		if ((*rd)[i] == 39 && count % 2 == 0)
		{
			i++;
			while ((*rd)[i] != 39)
				i++;
		}
		if ((*rd)[i] == '"')
			count++;
		if ((*rd)[i] == '$')
		{
			expander(str, all);
			*rd = *str;
			break ;
		}
	}
}

void	check_expanser(char **str, t_all *all)
{
	char	*rd;
	char	*tmp;

	rd = *str;
	tmp = ft_strdup(rd);
	check_exp_utils(&rd, str, all);
	if (ft_strlen(rd) < ft_strlen(tmp) && \
			(ft_strchr(tmp, '<') || ft_strchr(tmp, '>')))
	{
		free (rd);
		*str = tmp;
	}
	else
		free(tmp);
}
