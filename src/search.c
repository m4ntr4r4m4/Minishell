/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:03:08 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 18:03:09 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_cmd(t_all *all, char **str)
{
	int		x;
	int		bol;
	char	token;

	x = 0;
	all->size = 0;
	bol = 1;
	while (str[x])
	{
		token = tokens(str[x]);
		if (bol)
		{
			all->size++;
			bol = 0;
		}
		else if (token == PIPE || token == AMPERSAND)
			bol = 1;
		x++;
	}
}

int	search_util(char token, t_all *all, int *rol, int *i)
{
	if (token == CONTINUE)
	{
		if (*rol == 0)
			*rol = 1;
		else
			all->s_t++;
	}
	else if (token == PIPE || token == AMPERSAND)
	{
		(*i)++;
		return (0);
	}
	else
	{
		(*i)++;
		*rol = 0;
	}
	return (1);
}

int	search_arg(t_all *all, char **str)
{
	int			i;
	char		token;
	int			rol;

	all->s_t = 0;
	rol = 0;
	i = all->i_a;
	while (str[i])
	{
		token = tokens(str[i]);
		if (!search_util(token, all, &rol, &i))
			break ;
		i++;
	}
	all->i_a = i;
	return (++all->s_t);
}

void	search_files(t_all *all, char **str)
{
	int			i;
	char		token;

	all->s_i = 0;
	all->s_o = 0;
	all->s_eof = 0;
	i = all->i_f;
	while (str[i])
	{
		token = tokens(str[i]);
		if (token == LESS)
			all->s_i++;
		else if (token == LESSLESS)
			all->s_eof++;
		else if (token == GREAT || token == GREATGREAT)
			all->s_o++;
		else if (token == PIPE || token == AMPERSAND)
		{
			i++;
			break ;
		}
		++i;
	}
	all->i_f = i;
}
