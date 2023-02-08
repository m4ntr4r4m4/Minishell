/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/08 17:39:57 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_open_in(t_all *all, int *i, int *j)
{
	all->pipes[*i].fdin = open(all->cmd[*i].infile[0], O_RDONLY);
	if (all->pipes[*i].fdin < 0)
	{
		perror("file desc");
		exit(1);
	}
}

void	ft_open_out(t_all *all, int *i)
{
	int	j;

	j = -1;
	while (++j < all->s_o)
	{
		if (all->cmd[*i].token[1])
			all->pipes[*i].fdout = open(all->cmd[*i].outfile[j], \
			O_RDWR | O_TRUNC | O_CREAT, 0666);
	
		if (all->cmd[*i].token[3])
			all->pipes[*i].fdout = open(all->cmd[*i].outfile[j], \
			O_RDWR | O_APPEND , 0666);

		if (all->pipes[*i].fdout < 0)
		{
			perror("file desc");
			exit(1);
		}
	}
}


void	child1(t_all *all, int i, size_t size)
{
	int	j;

	all->pipes[i].fdin = -1;
	all->pipes[i].fdout = -1;
	if ((all->cmd[i].token[2] == 54 \
				|| all->cmd[i].token[0] == LESS))
		ft_open_in(all, &i, &j);
	if (i == (int) all->size - 1 && \
			(all->cmd[i].token[1] || all->cmd[i].token[3]))
		ft_open_out(all, &i);
	dupfd(all, i, size - 1);
	closefiledes(all->pipes, size - 1);

	int k = 0;
	while (ft_strncmp(all->myenv[k], "PWD", 3))
		k++;
	if (all->cmd[i].builtins)
	{
		if (all->size > 1)
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
	i = -1;
	while (++i < (int)all->size)
	{
		pid[i] = -1;
		pid[i] = fork();
		if (pid[i] == 0)
			child1(all, i, all->size);
	}
	i = 0;
	while (i < (int)all->size - 1)
	{
		close(all->pipes[i].fd[0]);
		close(all->pipes[i].fd[1]);
		i++;
	}
	i = -1;
	while (++i < (int)all->size)
		waitpid(pid[i], &all->exit_var, 0);
//	fprintf(stderr, "after exit value: %d\n", WEXITSTATUS(all->exit_var));
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
		if (all->cmd[0].builtins && all->size < 2)
			ft_builtins(all, 0);
	//	print_all(all);
		executor(all);
		freecmd(all);
	}
	return (0);
}
