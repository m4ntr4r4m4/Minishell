/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:39:19 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/13 20:26:14 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
