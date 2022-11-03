/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:30:53 by ahammoud          #+#    #+#             */
/*   Updated: 2022/11/03 18:32:02 by ahammoud         ###   ########.fr       */
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
	cmd->name = av[i];
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

void	child1(t_cmd *cmd, char **envp)
{
//	printf("SUCCESSS \n");
	if (execve(cmd->path, cmd->args, envp) < 0)
	{
		perror("command");
	}
}

int	executor(t_all *all, char **envp)
{
	int	*pid;
	int	i;

	i = 0;
//	printf("all size %zu\n", all->size);
	pid = malloc(sizeof(int) * all->size);
	while (i < all->size)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			child1(&all->cmd[i], envp);
		i++;
	}
	i = 0;
	while (i < all->size)
		waitpid(pid[i++], NULL, 0);
//	printf("++ ERORO\n");
	free(pid);
	return (0);
}
