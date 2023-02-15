/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:39:19 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/13 21:50:36 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tokens(char *str)
{
	int		i;
	char	token;
	char	prev;
	int		count;
	int		newcount;

	i = -1;
	count = 1;
	newcount = 0;
	while (str[++i])
	{
		token = token_l(str[i]);
		if (token != CONTINUE)
		{
			if (!count && !newcount)
				newcount = 1;
			else if (!count)
				return 0;
			count = 0;
			prev = token;
		}
		else if (str[i] != 32)
			count = 1;
	}
	if (!count)
		return (0);
	return (1);
}