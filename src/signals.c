/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:07:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/15 22:47:45 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handlerint(int x)
{
	if (x)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ioctl(0, TIOCSTI, "\n");
	}
}

void	handlersev(int x)
{
	if (x)
		kill(getpid(), SIGTSTP);
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
