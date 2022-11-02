/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:26:05 by ahammoud          #+#    #+#             */
/*   Updated: 2022/03/13 18:13:53 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dupfd(t_pip vars)
{
	dup2(vars.fdin, 0);
	dup2(vars.fd[1], 1);
	close(vars.fd[1]);
	close(vars.fd[0]);
	close(vars.fdin);
}

void	child1(t_pip vars, char **argv, char **envp)
{
	int	i;

	i = 0;
	vars.fdin = open(argv[1], O_RDONLY);
	if (vars.fdin < 0)
	{
		perror("error");
		exit(0);
	}
	dupfd(vars);
	vars.program = ft_split(argv[2], ' ');
	while (vars.pathvar[i])
	{
		vars.path = check_bin(vars.program[0], vars.pathvar[i++], 3);
		if (vars.path)
			break ;
	}
	if (!vars.path)
	{
		perror("command");
		exit(0);
	}
	execve(vars.path, vars.program, envp);
}

void	dupfd2(t_pip vars)
{
	dup2(vars.fdout, 1);
	dup2(vars.fd[0], 0);
	close(vars.fd[0]);
	close(vars.fd[1]);
	close(vars.fdout);
}

void	child2(t_pip vars, char **argv, char **envp)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	vars.fdout = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (vars.fdout < 0)
	{
		perror("error");
		exit(0);
	}
	dupfd2(vars);
	vars.program2 = ft_split(argv[3], ' ');
	while (vars.pathvar[i])
	{
		vars.path2 = check_bin(vars.program2[0], vars.pathvar[i++], 3);
		if (vars.path2)
			break ;
	}
	if (execve(vars.path2, vars.program2, envp) < 0)
	{
		perror("command");
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	vars;
	int		pid1;
	int		pid2;

	if (argc == 5)
	{
		if (pipe(vars.fd) < 0)
			return (0);
		vars.pathvar = path_var(envp);
		pid1 = fork();
		if (pid1 == 0)
			child1(vars, argv, envp);
		pid2 = fork();
		if (pid2 == 0)
			child2(vars, argv, envp);
		close(vars.fd[0]);
		close(vars.fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		freevars(&vars);
	}
	else
		ft_putstr_fd("example: ./pipex file1 cmd1 cmd2 file2\n", 1);
	return (0);
}
