/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/21 22:13:03 by ahammoud         ###   ########.fr       */
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
		perror(all->cmd[i].name);
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

void	ft_pre_here_doc(t_all *all)
{
	size_t	x;

	x = -1;
	while (++x < all->size)
	{
		if (all->cmd[x].token[2] == LESSLESS)
		{
			ft_here_doc(all);
			break ;
		}
	}
}

int	ft_check_token(int *str)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (str[i])
			return (1);

	return (0);
}

int	prexec(t_all *all)
{
	int	i;

	i = 0;
	if (all->size >= 1)
	{
		all->pipes = malloc(sizeof(t_pipe) * (all->size));
		if (!all->pipes)
			return (0);
		ft_pre_here_doc(all);
		if (all->cmd[0].builtins && all->size < 2 \
			&& !ft_check_token(all->cmd[0].token))
			ft_builtins(all, 0);
		else
			executor(all);
		freecmd(all);
	}
	return (0);
}
