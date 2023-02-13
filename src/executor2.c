/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/12 18:03:00 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	child1(t_all *all, int i)
{
	ft_open_fd(all, i);
	if (all->cmd[i].builtins)
	{
		if (all->size >= 1)
			ft_builtins(all, i);
	}
	else if (execve(all->cmd[i].path, all->cmd[i].args, all->myenv) < 0)
		perror("command");
	exit(errno);
}

void	executor(t_all *all)
{
	int	*pid;
	int	i;

	pid = malloc(sizeof(int) * all->size);
	if (!pid)
		exit(1);
	ft_pipes(all, pid);
	i = -1;
	while (++i < (int)all->size)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child1(all, i);
	}
	ft_close_parent(all);
	i = -1;
	while (++i < (int)all->size)
		waitpid(pid[i], &all->exit_var, 0);
	free(pid);
}

int	prexec(t_all *all)
{
	size_t	x;

	x = -1;
	if (all->size >= 1)
	{
		all->pipes = malloc(sizeof(t_pipe) * (all->size));
		if (!all->pipes)
			return (0);
		while (++x < all->size)
		{
			if (all->cmd[x].token[2] == LESSLESS)
			{
				ft_here_doc(all);
				break ;
			}
		}
		if (all->cmd[0].builtins && all->size < 2 && !all->cmd[0].token[1])
			ft_builtins(all, 0);
		else
			executor(all);
		freecmd(all);
	}
	return (0);
}
