/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:01:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 18:01:39 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (!strcmp(token, "<>"))
		return (LESS);
	else if (!strcmp(token, ">&"))
		return (GREATAMPERSAND);
	else if (!strcmp(token, "|"))
		return (PIPE);
	else if (!strcmp(token, "&"))
		return (AMPERSAND);
	else
		return (CONTINUE);
}
