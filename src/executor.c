/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2023/01/05 17:40:52 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	child1(t_all *all,  char **envp, int i,size_t size)
{
	int	j;
	all->pipes[i].fdin = -1;
	all->pipes[i].fdout = -1;
	if( all->cmd[0].n_tokens)
	{
		if (i == 0 && (all->cmd[i].token[0] == LESSLESS || all->cmd[i].token[0] == LESS))
		{
			all->pipes[i].fdin = open(all->cmd[i].infile[0], O_RDONLY);
			if (all->pipes[i].fdin < 0)
				fprintf(stderr,"this  errrorooo \n");
  		}
		if (i == (int) all->size - 1 && all->cmd[i].token[0] == GREAT)
		{
			j = -1;
			while (++j < all->s_o)
			{
				fprintf(stderr,"\n** this  is outfile %s\n", all->cmd[i].outfile[j]);
				all->pipes[i].fdout \
					= open(all->cmd[i].outfile[j], O_RDWR | O_TRUNC | O_CREAT, 0666);
				if (all->pipes[i].fdout < 0)
					fprintf(stderr,"this  errrorooo \n");
			}
		}
	}
	dupfd(all->pipes, i, size - 1);
	closefiledes(all->pipes, size - 1);
	if (execve(all->cmd[i].path, all->cmd[i].args, envp) < 0)
		perror("command");
}

int	executor(t_all *all, char **envp)
{
	int	*pid;
	int	i;

	pid = malloc(sizeof(int) * all->size);
	if(!pid)
		return(-1);
	i = 0;
	if (all->size > 1)
	{
		while (i < all->size - 1)
		{
			if (pipe(all->pipes[i].fd) < 0)
			{
				fprintf(stderr, "serror pipes \n");
				free(pid);
				return (-1);
			}
			fprintf(stderr, "success pipes \n");
			i++;
		}
	}

//	fprintf(stderr, "this  size %zu\n", all->size );
	i = -1;
	while (++i < all->size)
	{
		pid[i] = -1;
		pid[i] = fork();
		if (pid[i] == 0)
			child1(all, envp, i, all->size);
	}
	///////// clode file desc
	i = 0;

	while (i < all->size - 1)
	{
	//	fprintf(stderr," in parrent success closing\n");
		close(all->pipes[i].fd[0]);
		close(all->pipes[i].fd[1]);
		i++;
	}
	i = -1;
	while (++i < all->size)
	{
	//	kill(pid[i], SIGKILL);
		waitpid(pid[i], &all->exit_var, 0);
	}
	free(pid);
	return (0);
}

int	prexec(t_all *all, char **envp)
{
	if (all->size >= 1)
	{
		all->pipes = malloc(sizeof(t_pipe) * (all->size));
			if(!all->pipes)
				return (0);
		if (all->cmd[0].n_tokens)
			if (all->cmd[0].token[0] == LESSLESS)
				ft_here_doc(all);
		executor(all, envp);
		fprintf(stderr,"\nthis is the exit value:		%d\n", WEXITSTATUS(all->exit_var));
		freecmd(all);
	}
	return (0);
}
