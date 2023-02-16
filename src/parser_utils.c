/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:03:18 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 18:03:20 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	check_builtins(t_all *all)
{
	int	y;

	y = 0;
	while (y < (int)all->size)
	{
		if (!strcmp(all->cmd[y].name, "echo") \
	|| !strcmp(all->cmd[y].name, "unset") \
	|| !strcmp(all->cmd[y].name, "export") \
	|| !strcmp(all->cmd[y].name, "pwd") \
	|| !strcmp(all->cmd[y].name, "env") \
	|| !strcmp(all->cmd[y].name, "cd") \
	|| !strcmp(all->cmd[y].name, "exit"))
			all->cmd[y].builtins = 1;
		y++;
	}
}
