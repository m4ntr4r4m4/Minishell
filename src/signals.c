/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:07:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/12 18:07:46 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handlerint(int x)
{
	if (x)
	{
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

void	handlerquit(int x)
{
	if (x)
		rl_on_new_line();
}

void	mysignal(void)
{
	signal(SIGINT, handlerint);
	signal(SIGQUIT, handlerquit);
}
