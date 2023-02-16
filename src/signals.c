/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:07:37 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/16 14:05:45 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handlerint(int x)
{
	if (x)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
//		rl_redisplay();
//		printf("%s", rl_line_buffer);
//		rl_replace_line("", 0);
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
