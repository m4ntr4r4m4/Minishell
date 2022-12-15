/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2022/12/15 17:02:02 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

char	**path_var(char **envp)
{
	int		i;
	char	**pathvar;
	char	*str;
	char	*tmp;

	pathvar = NULL;
	i = 0;
	if(envp[0])
	{
		while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
			i++;
		tmp = ft_strtrim(envp[i], "PATH=");
		pathvar = ft_split(tmp, ':');
		i = 0;
		while (pathvar[i])
		{
			str = ft_strjoin(pathvar[i], "/");
			free(pathvar[i]);
			pathvar[i] = str;
			i++;
		}
		if (tmp)
			free(tmp);
	}
	return (pathvar);
}

char	*check_bin(char *binary, char *path, int ac)
{
	int		x;

	if (ac == 2)
		x = access(ft_strjoin(path, binary), W_OK);
	if (ac == 1)
		x = access(ft_strjoin(path, binary), R_OK);
	if (ac == 3)
		x = access(ft_strjoin(path, binary), X_OK);
	if (x == 0)
		return (ft_strjoin(path, binary));
	return (NULL);
}

char	*get_path(char **pathvar, char *cmd, int code)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (pathvar[i])
	{
		path = check_bin(cmd, pathvar[i++], code);
		if (path)
			break ;
	}
	return (path);
}

void	dupfd(t_pipe *pipes, int id, size_t size)
{
	int	i;

	i = 0;
	if (id == 0)
	{
		dup2(pipes[id].fdin, 0);
		close(pipes[id].fd[0]);
		close(pipes[id].fdin);
	}
	if (id > 0)
	{
		dup2(pipes[id - 1].fd[0], 0);
		close(pipes[id - 1].fd[0]);
	}
	if(id < size)
	{
		dup2(pipes[id].fd[1], 1);
		close(pipes[id].fd[1]);
	}
	if(id == size)
	{
		dup2(pipes[id - 1].fdout, 1);
		close(pipes[id - 1].fdout);
	}

}

void	closefiledes(t_pipe *var, int x, size_t size)
{
	int	i;

	i = 0;
	while (i < size )
	{
		close(var[i].fd[0]);
		close(var[i].fd[1]);
		i++;
	}
}

void	child1(t_all *all,  char **envp, int i,size_t size)
{
	int	y;
	if (i == 0 && !strncmp(all->cmd[0].token, "5", 0))
	{
		fprintf(stderr,"do not enter here \n");
		all->pipes[i].fdin = open(all->cmd[0].infile[0], O_RDONLY);
		fprintf(stderr,"this  is infile %s\n", all->cmd[0].infile[0]);
		if (all->pipes[i].fdin < 0)
			fprintf(stderr,"this  errrorooo \n");
	}
	if (i == (int) all->size - 1 && !strncmp(all->cmd[0].token, "2", 0))
	{
		fprintf(stderr,"this  is outfile %s\n", all->cmd[i].outfile[0]);
		all->pipes[i - 1].fdout \
			= open(all->cmd[i].outfile[0], O_RDWR | O_TRUNC | O_CREAT, 0666);
		if (all->pipes[i - 1].fdout < 0)
			fprintf(stderr,"this  errrorooo \n");
	}
	dupfd(all->pipes, i, size - 1);
	closefiledes(all->pipes, i, size - 1);
	if ( (y = execve(all->cmd[i].path, all->cmd[i].args, envp)) < 0)
		perror("command");
//	fprintf(stderr, "error code %d\n", y);
}

int	executor(t_all *all, char **envp)
{
	int	*pid;
	int	i;

	pid = malloc(sizeof(int) * all->size);
	i = 0;
	if (all->size > 1)
	{
		while (i < all->size - 1)
		{
			if (pipe(all->pipes[i].fd) < 0)
			{
				fprintf(stderr, "serror pipes \n");
				return (0);
			}
			fprintf(stderr, "success pipes \n");
			i++;
		}
	}
	i = 0;
	while (i < all->size)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child1(all, envp, i, all->size);
		i++;
	}
	///////// clode file desc
	i = 0;

	while (i < all->size - 1)
	{
		fprintf(stderr," in parrent success closing\n");
		close(all->pipes[i].fd[0]);
		close(all->pipes[i].fd[1]);
		i++;
	}
	i = 0;
	while (i < all->size)
		waitpid(pid[i++], NULL, 0);
	free(pid);
	return (0);
}

int	prexec(t_all *all, char **envp)
{
	int	x;

	x = 0;
	if (all->size > 1)
		all->pipes = malloc(sizeof(t_pipe) * (all->size - 1));
			if(!all->cmd)
				return (0);
	else if (all->size >= 1)
	{
		x = executor(all, envp);
		freecmd(all);
	}
	return (x);
}
