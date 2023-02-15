/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/15 13:18:17 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_open_in(t_all *all, int *i)
{
	int	j;

	j = -1;
	while (++j < ft_get_size(all->cmd[*i].infile))
	{
		all->pipes[*i].fdin = open(all->cmd[*i].infile[j], O_RDONLY);
		if (all->pipes[*i].fdin < 0)
		{
			perror(all->cmd[*i].infile[0]);
			exit(errno);
		}
	}
}

void	ft_open_out(t_all *all, int *i)
{
	int	j;

	j = 0;
	while (all->cmd[*i].outfile[j + 1])
		open(all->cmd[*i].outfile[j++], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (all->cmd[*i].token[1])
	{
		all->pipes[*i].fdout = open(all->cmd[*i].outfile[j], \
		O_RDWR | O_TRUNC | O_CREAT, 0666);
	}	
	if (all->cmd[*i].token[3])
		all->pipes[*i].fdout = open(all->cmd[*i].outfile[j], \
	O_RDWR | O_APPEND | O_CREAT, 0666);
	if (all->pipes[*i].fdout < 0)
	{
		perror(all->cmd[*i].outfile[j]);
		exit(1);
	}
}

void	ft_open_fd(t_all *all, int i)
{
	all->pipes[i].fdin = -1;
	all->pipes[i].fdout = -1;
	if ((all->cmd[i].token[2] == 54 \
				|| all->cmd[i].token[0] == LESS))
		ft_open_in(all, &i);
	if ((all->cmd[i].token[1] || all->cmd[i].token[3]))
		ft_open_out(all, &i);
	dupfd(all, i, all->size - 1);
	closefiledes(all->pipes, all->size - 1);
}

void	ft_close_parent(t_all *all)
{
	int	i;

	i = 0;
	while (i < (int)all->size - 1)
	{
		close(all->pipes[i].fd[0]);
		close(all->pipes[i].fd[1]);
		i++;
	}
}

void	ft_pipes(t_all *all, int *pid)
{
	int	i;

	i = 0;
	if (all->size > 1)
	{
		while (i < (int) all->size - 1)
		{
			if (pipe(all->pipes[i].fd) < 0)
			{
				free(pid);
				exit(1);
			}
			i++;
		}
	}
}
