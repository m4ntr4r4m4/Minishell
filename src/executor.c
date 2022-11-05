/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/05 17:10:00 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**path_var(char **envp)
{
	int		i;
	char	**pathvar;
	char	*str;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	envp[i] = ft_strtrim(envp[i], "PATH=");
	pathvar = ft_split(envp[i], ':');
	i = 0;
	while (pathvar[i])
	{
		str = ft_strjoin(pathvar[i], "/");
		free(pathvar[i]);
		pathvar[i] = str;
		i++;
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

void	cmd_init(t_cmd *cmd, int ac, char **av, char **envp)
{
	int		i;

	i = 0;
	cmd->num_args = ac - 1;
//	printf("number args %d\n",cmd->num_args);
//	ft_print_table(av, 1);
	cmd->name = strdup(av[i]);
	cmd->args = malloc(sizeof(char *) * (cmd->num_args + 2));
	if (!cmd->args)
		exit (0);
	cmd->path = get_path(cmd->pathvar, cmd->name, 3);
	cmd->args[i++] = cmd->path;
	cmd->args[cmd->num_args + 1] = NULL;
	while (i <= cmd->num_args)
	{
//		printf("******************  %d av : %s\n------\n",i, av[i]);
		cmd->args[i] = ft_strdup(av[i]);
		i++;
	}
}

void	dupfd(t_pipe vars, int i, size_t size)
{
//	fprintf(stderr,"id fd: %d \n (i + 1) %%2: %d \n", i, (i + 1) % 2);
	dup2(vars.fd[(i + 1) % 2], (i + 1) % 2);
//	dup2(vars.fd[i], i);
//		close(vars.fd[(i + 1) % 2]);
//		close(vars.fd[i]);
	close(vars.fd[1]);
	close(vars.fd[0]);
//	close(vars.fdin);
}

void	closefiledes(t_pipe *var, int x, size_t size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (i != x)
		{
			close(var[i].fd[0]);
			close(var[i].fd[1]);
			i++;
		}
		else
			i++;
	}
}

void	child1(t_all *all,  char **envp, int i,size_t size)
{
	int	x;

	if (i == 0)
		x = 0;
	else
		x = (i + 1) % size;

	////// duplicat file desc 

	
	dupfd(all->pipes[x], i, size);
	closefiledes(all->pipes, x, size - 1);

	fprintf(stderr, "SUCCESSS cmd : %s\n", all->cmd[i].name);
	if (execve(all->cmd[i].path, all->cmd[i].args, envp) < 0)
	{
		perror("command");
	}
}

int	executor(t_all *all, char **envp)
{
	int	*pid;
	int	i;

	printf("all size %zu\n", all->size);
	pid = malloc(sizeof(int) * all->size);
	i = 0;

	if (all->size > 1)
	{
		while (i < all->size - 1)
		{
			if (pipe(all->pipes[i++].fd) < 0)
			{
				fprintf(stderr, "serror pipes \n");
				return (0);
			}
		}
	}
		
	fprintf(stderr, "success pipes \n");
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

	x = executor(all, envp);


	return (x);
}
