/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2023/02/07 16:31:00 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_open_in(t_all *all, int *i, int *j)
{
	fprintf(stderr, "************//// %d  %d    ///////////********\n", *i, *j);
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
			O_RDWR | O_APPEND | O_TRUNC | O_CREAT, 0666);

		if (all->pipes[*i].fdout < 0)
		{
			perror("file desc");
			exit(1);
		}
	}
}

void	ft_builtins(t_all *all, int *j)
{
	int	i;
	int	x;

	i = *j;
	x = 0;
	if (!strncmp(all->cmd[i].name, "echo", 4))
		while (all->cmd[i].args[x])
			ft_echo(all->cmd[i].args[x++], 1);	
	if (!strncmp(all->cmd[i].name, "pwd", 3))
		ft_pwd();
	if (!strncmp(all->cmd[i].name, "cd", 2))
		ft_cd(all->cmd[i].args[0], all);
	x = 0;
	if (!strncmp(all->cmd[i].name, "unset", 5))
		while (all->cmd[i].args[x])
			ft_unset(all->cmd[i].args[x++], all);
	if (!strncmp(all->cmd[i].name, "exit", 4))
		ft_exit();
}

void	child1(t_all *all, char **envp, int i, size_t size)
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
	if (all->cmd[i].builtins)
		ft_builtins(all, &i);
	else if (execve(all->cmd[i].path, all->cmd[i].args, envp) < 0)
		perror("command");
	kill(getpid(), SIGTERM);
}

void	executor(t_all *all, char **envp)
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
			child1(all, envp, i, all->size);
	}
	i = 0;
	while (i < (int)all->size - 1)
	{
		close(all->pipes[i].fd[0]);
		close(all->pipes[i].fd[1]);
		i++;
	}
	i = -1;
	fprintf(stderr, "beforeexit value: %d\n", WEXITSTATUS(all->exit_var));
	while (++i < (int)all->size)
		waitpid(pid[i], &all->exit_var, 0);
	fprintf(stderr, "after exit value: %d\n", WEXITSTATUS(all->exit_var));
	free(pid);
}

int	prexec(t_all *all, char **envp)
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
	//	print_all(all);
		executor(all, envp);
		freecmd(all);
	}
	return (0);
}
